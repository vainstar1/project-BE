// Mod auto-updater. At start-up a background thread asks GitHub for the latest release of the mod. When it is newer
// than this DLL, the main menu shows the game's own Yes/No message ("Update" / "Later"). "Later" leaves an entry on
// the main menu billboard so the player can update whenever they like.
// Updating downloads the release zip, swaps the files next to this DLL (a loaded DLL can be renamed, not
// overwritten), then restarts the game through our launcher, which waits for this process to exit.
#include <windows.h>
#include <winhttp.h>
#include <string>
#include <vector>
#include <cstdio>
#include "ue.h"
#include "mod.h"

namespace update {
namespace {
const wchar_t* kHost = L"api.github.com";
const wchar_t* kPath = L"/repos/vainstar1/project-BE/releases/latest";
const char* kAsset = "BE1v1.zip";

volatile LONG gState;           // 0 = checking, 1 = up to date / failed, 2 = update available
std::string gLatest, gAssetUrl, gNotes;
bool gPrompted, gBusy, gPostponed;

// Minimal HTTPS GET with redirects (GitHub release assets redirect to a CDN host).
bool HttpGet(const std::wstring& url, std::string& out, const wchar_t* accept = L"application/vnd.github+json") {
    std::wstring u = url;
    for (int hop = 0; hop < 5; hop++) {
        URL_COMPONENTS uc{}; uc.dwStructSize = sizeof uc;
        wchar_t host[256], path[2048];
        uc.lpszHostName = host; uc.dwHostNameLength = 256; uc.lpszUrlPath = path; uc.dwUrlPathLength = 2048;
        wchar_t extra[2048]; uc.lpszExtraInfo = extra; uc.dwExtraInfoLength = 2048;
        if (!WinHttpCrackUrl(u.c_str(), 0, 0, &uc)) return false;
        std::wstring fullPath = std::wstring(path) + extra;
        HINTERNET s = WinHttpOpen(L"BE1v1-Updater", WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY, nullptr, nullptr, 0);
        if (!s) return false;
        WinHttpSetTimeouts(s, 10000, 10000, 15000, 60000);
        HINTERNET c = WinHttpConnect(s, host, uc.nPort, 0);
        HINTERNET r = c ? WinHttpOpenRequest(c, L"GET", fullPath.c_str(), nullptr, nullptr, nullptr, WINHTTP_FLAG_SECURE) : nullptr;
        DWORD noRedirect = WINHTTP_DISABLE_REDIRECTS;
        if (r) WinHttpSetOption(r, WINHTTP_OPTION_DISABLE_FEATURE, &noRedirect, sizeof noRedirect);
        std::wstring hdr = std::wstring(L"Accept: ") + accept;
        bool ok = r && WinHttpSendRequest(r, hdr.c_str(), (DWORD)-1, nullptr, 0, 0, 0) && WinHttpReceiveResponse(r, nullptr);
        DWORD status = 0, sz = sizeof status;
        if (ok) WinHttpQueryHeaders(r, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, nullptr, &status, &sz, nullptr);
        std::wstring location;
        if (ok && (status == 301 || status == 302 || status == 303 || status == 307 || status == 308)) {
            wchar_t loc[4096]; DWORD ls = sizeof loc;
            if (WinHttpQueryHeaders(r, WINHTTP_QUERY_LOCATION, nullptr, loc, &ls, nullptr)) location = loc;
        } else if (ok && status == 200) {
            out.clear();
            for (;;) {
                DWORD avail = 0;
                if (!WinHttpQueryDataAvailable(r, &avail) || !avail) break;
                std::vector<char> buf(avail); DWORD got = 0;
                if (!WinHttpReadData(r, buf.data(), avail, &got) || !got) break;
                out.append(buf.data(), got);
            }
        }
        if (r) WinHttpCloseHandle(r);
        if (c) WinHttpCloseHandle(c);
        WinHttpCloseHandle(s);
        if (!location.empty()) { u = location; continue; }
        return ok && status == 200;
    }
    return false;
}

// Tiny JSON string field reader (the release JSON is flat enough for this).
std::string JsonStr(const std::string& j, const std::string& key, size_t from = 0, size_t* at = nullptr) {
    size_t p = j.find("\"" + key + "\"", from);
    if (p == std::string::npos) return "";
    p = j.find(':', p); if (p == std::string::npos) return "";
    p = j.find('"', p); if (p == std::string::npos) return "";
    std::string r;
    for (size_t i = p + 1; i < j.size() && j[i] != '"'; i++) {
        if (j[i] == '\\' && i + 1 < j.size()) { i++; r += j[i] == 'n' ? '\n' : j[i]; } else r += j[i];
    }
    if (at) *at = p;
    return r;
}

// "v2.1.0" > "2.0.3" ?
bool Newer(const std::string& a, const std::string& b) {
    int x[3] = {}, y[3] = {};
    sscanf(a.c_str() + (a[0] == 'v' || a[0] == 'V'), "%d.%d.%d", &x[0], &x[1], &x[2]);
    sscanf(b.c_str() + (b[0] == 'v' || b[0] == 'V'), "%d.%d.%d", &y[0], &y[1], &y[2]);
    for (int i = 0; i < 3; i++) if (x[i] != y[i]) return x[i] > y[i];
    return false;
}

DWORD WINAPI CheckThread(void*) {
    Sleep(3000);
    std::string body;
    if (!HttpGet(std::wstring(L"https://") + kHost + kPath, body)) { Log("update: check failed"); InterlockedExchange(&gState, 1); return 0; }
    gLatest = JsonStr(body, "tag_name");
    // asset download url: find the asset whose "name" is BE1v1.zip, then its browser_download_url
    size_t at = 0, from = 0;
    while (true) {
        std::string name = JsonStr(body, "name", from, &at);
        if (name.empty()) break;
        from = at + 1;
        if (name == kAsset) { gAssetUrl = JsonStr(body, "browser_download_url", at); break; }
    }
    Log("update: latest=%s mine=%s asset=%s", gLatest.c_str(), BE1V1_VERSION, gAssetUrl.empty() ? "-" : "yes");
    InterlockedExchange(&gState, (!gLatest.empty() && !gAssetUrl.empty() && Newer(gLatest, BE1V1_VERSION)) ? 2 : 1);
    return 0;
}

std::wstring TempDir() { wchar_t t[MAX_PATH]; GetTempPathW(MAX_PATH, t); return std::wstring(t) + L"be1v1-update\\"; }

bool RunWait(const std::wstring& cmd, DWORD timeoutMs) {
    STARTUPINFOW si{}; si.cb = sizeof si; si.dwFlags = STARTF_USESHOWWINDOW; si.wShowWindow = SW_HIDE;
    PROCESS_INFORMATION pi{};
    std::wstring c = cmd;
    if (!CreateProcessW(nullptr, &c[0], nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi)) return false;
    DWORD w = WaitForSingleObject(pi.hProcess, timeoutMs);
    DWORD code = 1; GetExitCodeProcess(pi.hProcess, &code);
    CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
    return w == WAIT_OBJECT_0 && code == 0;
}

volatile LONG gApplyResult;   // 0 running, 1 ok, 2 failed
DWORD WINAPI ApplyThread(void*) {
    std::wstring dir = TempDir();
    RunWait(L"cmd.exe /c rmdir /s /q \"" + dir + L"\"", 10000);
    CreateDirectoryW(dir.c_str(), nullptr);
    std::string zip;
    if (!HttpGet(Utf8ToWide(gAssetUrl), zip, L"application/octet-stream") || zip.size() < 1000) { Log("update: download failed"); InterlockedExchange(&gApplyResult, 2); return 0; }
    std::wstring zipPath = dir + L"BE1v1.zip";
    FILE* f = _wfopen(zipPath.c_str(), L"wb");
    if (!f) { InterlockedExchange(&gApplyResult, 2); return 0; }
    fwrite(zip.data(), 1, zip.size(), f); fclose(f);
    // Windows 10+ ships bsdtar, which reads zip files.
    wchar_t sys[MAX_PATH]; GetSystemDirectoryW(sys, MAX_PATH);
    std::wstring out = dir + L"x\\";
    CreateDirectoryW(out.c_str(), nullptr);
    if (!RunWait(L"\"" + std::wstring(sys) + L"\\tar.exe\" -xf \"" + zipPath + L"\" -C \"" + out + L"\"", 60000)) { Log("update: extract failed"); InterlockedExchange(&gApplyResult, 2); return 0; }
    // The zip holds BE1v1\BE1v1.exe and BE1v1\be1v1.dll (or the files at its root).
    std::wstring src = out + L"BE1v1\\";
    if (GetFileAttributesW((src + L"be1v1.dll").c_str()) == INVALID_FILE_ATTRIBUTES) src = out;
    std::wstring mod = ModDir();
    std::wstring dll = mod + L"be1v1.dll";
    DeleteFileW((dll + L".old").c_str());
    if (!MoveFileExW(dll.c_str(), (dll + L".old").c_str(), MOVEFILE_REPLACE_EXISTING) ||
        !CopyFileW((src + L"be1v1.dll").c_str(), dll.c_str(), FALSE)) {
        Log("update: replacing the DLL failed (%lu)", GetLastError());
        MoveFileExW((dll + L".old").c_str(), dll.c_str(), MOVEFILE_REPLACE_EXISTING);
        InterlockedExchange(&gApplyResult, 2); return 0;
    }
    // The installer/launcher: installs the new Launch_Game.exe into the game folder (it is not running now).
    CopyFileW((src + L"BE1v1.exe").c_str(), (mod + L"BE1v1.exe").c_str(), FALSE);
    if (GetFileAttributesW((src + L"README.txt").c_str()) != INVALID_FILE_ATTRIBUTES) CopyFileW((src + L"README.txt").c_str(), (mod + L"README.txt").c_str(), FALSE);
    Log("update: files replaced with %s", gLatest.c_str());
    InterlockedExchange(&gApplyResult, 1);
    return 0;
}

void Restart() {
    // BE1v1.exe --relaunch <pid>: refreshes Launch_Game.exe, waits for us to exit, then starts the game again.
    std::wstring exe = ModDir() + L"BE1v1.exe";
    std::wstring cmd = L"\"" + exe + L"\" --relaunch " + std::to_wstring(GetCurrentProcessId());
    STARTUPINFOW si{}; si.cb = sizeof si; PROCESS_INFORMATION pi{};
    if (CreateProcessW(exe.c_str(), &cmd[0], nullptr, nullptr, FALSE, 0, nullptr, ModDir().c_str(), &si, &pi)) {
        CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
        Log("update: restarting");
        TerminateProcess(GetCurrentProcess(), 0);
    } else {
        ui::ShowMessage(L"", L"BE1v1 has been updated. Restart the game to finish.");
    }
}
}  // namespace

bool Available() { return gState == 2; }
bool Postponed() { return gPostponed; }
std::wstring LatestVersion() { return Utf8ToWide(gLatest); }

void Begin() {
    if (gBusy || !Available()) return;
    gBusy = true;
    gApplyResult = 0;
    ui::ShowBusy(true);
    CloseHandle(CreateThread(nullptr, 0, ApplyThread, nullptr, 0, nullptr));
}

void Install() {
    std::wstring cmd = GetCommandLineW();
    if (cmd.find(L"-be1v1noupdate") != std::wstring::npos) { gState = 1; return; }
    CloseHandle(CreateThread(nullptr, 0, CheckThread, nullptr, 0, nullptr));
}

void Tick(float) {
    static bool cmdl = GetCommandLineW() && wcsstr(GetCommandLineW(), L"-be1v1updatetest");
    if (cmdl && gState == 1) { gLatest = "v9.9.9"; gAssetUrl = "https://example.invalid/BE1v1.zip"; gState = 2; cmdl = false; }
    if (gBusy) {
        LONG r = gApplyResult;
        if (r == 0) return;
        gBusy = false;
        ui::ShowBusy(false);
        if (r == 1) Restart();
        else ui::ShowMessage(L"", L"The update couldn't be downloaded. Try again later.");
        return;
    }
    // Ask once, on the main menu, when not in the middle of something.
    if (gState == 2 && !gPrompted && net::MenuSettled() && !lobby::Active() && ui::MainMenuReady()) {
        gPrompted = true;
        ui::Ask(L"A new version of BE1v1 is available (" + Utf8ToWide(gLatest) + L").", L"UPDATE", L"LATER",
                [](bool yes) { if (yes) Begin(); else gPostponed = true; });
    }
}
}  // namespace update
