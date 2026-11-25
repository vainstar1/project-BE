// BE1v1.exe - one program, three jobs:
//  * Double-clicked (any name except Launch_Game.exe): installs the mod into the Bleeding Edge folder and starts the
//    game through Steam. Installing = copy itself and be1v1.dll to <game>\BE1v1\, keep Steam's original launcher as
//    Launch_Game.eac.exe and put a copy of itself in its place as Launch_Game.exe. From then on Steam's Play button
//    (and Steam invites / "Join Game") start the game with the mod, and the Steam overlay works.
//  * Named Launch_Game.exe (started by Steam): starts MobladeClient-Win64-Shipping.exe with be1v1.dll loaded before
//    its first instruction, passes Steam's arguments through, and waits for the game like the original launcher did.
//    If the mod files are missing it runs the original launcher, so the game always starts.
//  * --relaunch <pid> (used by the in-game updater): waits for the old game to exit, refreshes Launch_Game.exe,
//    then starts the game again through Steam. --uninstall restores the original launcher.
#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include <commdlg.h>
#include <tlhelp32.h>
#include <string>
#include <vector>
#include <cstdio>

#include "inject.h"

namespace {
const wchar_t* kTitle = L"Bleeding Edge";
const wchar_t* kAppId = L"1189800";
const wchar_t* kGameRel = L"\\Moblade\\Binaries\\Win64\\MobladeClient-Win64-Shipping.exe";

std::wstring SelfPath() { wchar_t p[MAX_PATH]; GetModuleFileNameW(nullptr, p, MAX_PATH); return p; }
std::wstring DirOf(const std::wstring& p) { return p.substr(0, p.find_last_of(L"\\/")); }
std::wstring NameOf(const std::wstring& p) { return p.substr(p.find_last_of(L"\\/") + 1); }
bool Exists(const std::wstring& p) { return GetFileAttributesW(p.c_str()) != INVALID_FILE_ATTRIBUTES; }
bool IsFile(const std::wstring& p) { DWORD a = GetFileAttributesW(p.c_str()); return a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY); }

std::wstring RegStr(HKEY root, const wchar_t* key, const wchar_t* val) {
    wchar_t buf[1024]; DWORD sz = sizeof buf;
    if (RegGetValueW(root, key, val, RRF_RT_REG_SZ, nullptr, buf, &sz) == ERROR_SUCCESS) return buf;
    return L"";
}
DWORD RegDword(HKEY root, const wchar_t* key, const wchar_t* val) {
    DWORD v = 0, sz = sizeof v; RegGetValueW(root, key, val, RRF_RT_REG_DWORD, nullptr, &v, &sz); return v;
}
std::wstring ReadText(const std::wstring& path) {
    FILE* f = _wfopen(path.c_str(), L"rb"); if (!f) return L"";
    std::string s; char buf[4096]; size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, n);
    fclose(f);
    int wn = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
    std::wstring w(wn, L' '); MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), &w[0], wn);
    return w;
}
std::vector<std::wstring> VdfValues(const std::wstring& text, const std::wstring& key) {
    std::vector<std::wstring> out; std::wstring pat = L"\"" + key + L"\"";
    for (size_t p = text.find(pat); p != std::wstring::npos; p = text.find(pat, p + 1)) {
        size_t a = text.find(L'"', p + pat.size()); if (a == std::wstring::npos) break;
        size_t b = text.find(L'"', a + 1); if (b == std::wstring::npos) break;
        std::wstring v = text.substr(a + 1, b - a - 1), r;
        for (size_t i = 0; i < v.size(); i++) { if (v[i] == L'\\' && i + 1 < v.size() && v[i + 1] == L'\\') i++; r += v[i]; }
        out.push_back(r);
    }
    return out;
}

// Game root folder (the one holding Launch_Game.exe and Moblade\).
std::wstring FindGameRoot() {
    std::wstring steam = RegStr(HKEY_CURRENT_USER, L"Software\\Valve\\Steam", L"SteamPath");
    std::vector<std::wstring> libs;
    if (!steam.empty()) {
        libs.push_back(steam);
        for (auto& l : VdfValues(ReadText(steam + L"/steamapps/libraryfolders.vdf"), L"path")) libs.push_back(l);
    }
    for (auto& lib : libs) {
        std::wstring manifest = lib + L"\\steamapps\\appmanifest_" + kAppId + L".acf";
        if (!IsFile(manifest)) continue;
        auto dirs = VdfValues(ReadText(manifest), L"installdir");
        std::wstring root = lib + L"\\steamapps\\common\\" + (dirs.empty() ? L"Bleeding Edge" : dirs[0]);
        for (auto& c : root) if (c == L'/') c = L'\\';
        if (IsFile(root + kGameRel)) return root;
    }
    return L"";
}

bool SteamRunning() {
    DWORD pid = RegDword(HKEY_CURRENT_USER, L"Software\\Valve\\Steam\\ActiveProcess", L"pid");
    if (!pid) return false;
    HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!h) return false;
    DWORD code = 0; GetExitCodeProcess(h, &code); CloseHandle(h);
    return code == STILL_ACTIVE;
}
DWORD GamePid() {
    HANDLE s = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); PROCESSENTRY32W e{}; e.dwSize = sizeof e; DWORD pid = 0;
    for (BOOL ok = Process32FirstW(s, &e); ok; ok = Process32NextW(s, &e))
        if (!_wcsicmp(e.szExeFile, L"MobladeClient-Win64-Shipping.exe")) pid = e.th32ProcessID;
    CloseHandle(s); return pid;
}

void Message(const std::wstring& text, UINT icon = MB_ICONINFORMATION) { MessageBoxW(nullptr, text.c_str(), kTitle, MB_OK | icon | MB_SETFOREGROUND); }

// Is the file at `p` one of our own builds? (Our executables carry this marker string.)
const char kMarker[] = "BE1v1-launcher-marker-7d3f";
bool IsOurs(const std::wstring& p) {
    FILE* f = _wfopen(p.c_str(), L"rb"); if (!f) return false;
    std::string data; char buf[65536]; size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) data.append(buf, n);
    fclose(f);
    return data.find(kMarker) != std::string::npos;
}
volatile const char* gKeepMarker = kMarker;

bool CopyIfDifferent(const std::wstring& from, const std::wstring& to) {
    if (!_wcsicmp(from.c_str(), to.c_str())) return true;
    return CopyFileW(from.c_str(), to.c_str(), FALSE) != 0;
}

// ---- install ----------------------------------------------------------------------------------------------------
enum class Result { Ok, AccessDenied, Failed };
Result Install(const std::wstring& root, const std::wstring& srcDir, std::wstring* err) {
    std::wstring modDir = root + L"\\BE1v1";
    CreateDirectoryW(modDir.c_str(), nullptr);
    auto fail = [&](const std::wstring& what) {
        DWORD e = GetLastError();
        *err = what + L" (" + std::to_wstring(e) + L")";
        return e == ERROR_ACCESS_DENIED ? Result::AccessDenied : Result::Failed;
    };
    if (!Exists(modDir)) return fail(L"Couldn't create " + modDir);
    std::wstring self = SelfPath();
    if (!CopyIfDifferent(self, modDir + L"\\BE1v1.exe")) return fail(L"Couldn't copy BE1v1.exe");
    std::wstring dll = srcDir + L"\\be1v1.dll";
    if (IsFile(dll) && !CopyIfDifferent(dll, modDir + L"\\be1v1.dll")) {
        // The game may still hold the old DLL; a loaded DLL can be renamed out of the way.
        DeleteFileW((modDir + L"\\be1v1.dll.old").c_str());
        MoveFileExW((modDir + L"\\be1v1.dll").c_str(), (modDir + L"\\be1v1.dll.old").c_str(), MOVEFILE_REPLACE_EXISTING);
        if (!CopyFileW(dll.c_str(), (modDir + L"\\be1v1.dll").c_str(), FALSE)) return fail(L"Couldn't copy be1v1.dll");
    }
    if (!IsFile(modDir + L"\\be1v1.dll")) { SetLastError(ERROR_FILE_NOT_FOUND); return fail(L"be1v1.dll is missing next to BE1v1.exe"); }
    if (IsFile(srcDir + L"\\README.txt")) CopyIfDifferent(srcDir + L"\\README.txt", modDir + L"\\README.txt");
    // Swap Steam's launcher for ours, keeping the original.
    std::wstring launch = root + L"\\Launch_Game.exe", eac = root + L"\\Launch_Game.eac.exe";
    if (IsFile(launch) && !IsOurs(launch)) {
        DeleteFileW(eac.c_str());
        if (!MoveFileW(launch.c_str(), eac.c_str())) return fail(L"Couldn't rename Launch_Game.exe");
    }
    if (!CopyIfDifferent(self, launch)) return fail(L"Couldn't write Launch_Game.exe");
    return Result::Ok;
}

void Uninstall(const std::wstring& root) {
    std::wstring launch = root + L"\\Launch_Game.exe", eac = root + L"\\Launch_Game.eac.exe";
    if (IsFile(eac)) { DeleteFileW(launch.c_str()); MoveFileW(eac.c_str(), launch.c_str()); }
    std::wstring mod = root + L"\\BE1v1";
    WIN32_FIND_DATAW fd; HANDLE h = FindFirstFileW((mod + L"\\*").c_str(), &fd);
    if (h != INVALID_HANDLE_VALUE) {
        do { if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) DeleteFileW((mod + L"\\" + fd.cFileName).c_str()); } while (FindNextFileW(h, &fd));
        FindClose(h);
    }
    RemoveDirectoryW(mod.c_str());
}

bool RunElevated(const std::wstring& args) {
    std::wstring self = SelfPath();
    SHELLEXECUTEINFOW sei{}; sei.cbSize = sizeof sei; sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.lpVerb = L"runas"; sei.lpFile = self.c_str(); sei.lpParameters = args.c_str(); sei.nShow = SW_HIDE;
    if (!ShellExecuteExW(&sei) || !sei.hProcess) return false;
    WaitForSingleObject(sei.hProcess, INFINITE);
    DWORD code = 1; GetExitCodeProcess(sei.hProcess, &code); CloseHandle(sei.hProcess);
    return code == 0;
}

void StartThroughSteam() { ShellExecuteW(nullptr, L"open", L"steam://rungameid/1189800", nullptr, nullptr, SW_SHOWNORMAL); }

std::wstring Quote(const std::wstring& a) {
    if (a.find_first_of(L" \t\"") == std::wstring::npos && !a.empty()) return a;
    std::wstring r = L"\"";
    for (wchar_t c : a) { if (c == L'"') r += L'\\'; r += c; }
    return r + L"\"";
}

// ---- Launch_Game.exe mode -------------------------------------------------------------------------------------
int RunAsGameLauncher(int argc, wchar_t** argv) {
    std::wstring root = DirOf(SelfPath());
    std::wstring args;
    for (int i = 1; i < argc; i++) { if (!args.empty()) args += L" "; args += Quote(argv[i]); }
    std::wstring dll = root + L"\\BE1v1\\be1v1.dll", game = root + kGameRel;
    if (!IsFile(dll) || !IsFile(game)) {
        // Mod removed: behave exactly like Steam's own launcher.
        std::wstring eac = root + L"\\Launch_Game.eac.exe";
        std::wstring cmd = Quote(eac) + L" " + args;
        STARTUPINFOW si{}; si.cb = sizeof si; PROCESS_INFORMATION pi{};
        if (!CreateProcessW(eac.c_str(), &cmd[0], nullptr, nullptr, FALSE, 0, nullptr, root.c_str(), &si, &pi)) return 1;
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
        return 0;
    }
    PROCESS_INFORMATION pi{}; std::wstring err;
    if (!LaunchWithDll(game, args, dll, &pi, &err)) { Message(L"Bleeding Edge couldn't start: " + err, MB_ICONERROR); return 1; }
    CloseHandle(pi.hThread);
    WaitForSingleObject(pi.hProcess, INFINITE);   // Steam shows the game as running while we wait
    CloseHandle(pi.hProcess);
    return 0;
}
}  // namespace

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    int argc = 0; wchar_t** argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    std::wstring self = SelfPath();
    if (!_wcsicmp(NameOf(self).c_str(), L"Launch_Game.exe")) return RunAsGameLauncher(argc, argv);

    std::wstring mode = argc > 1 ? argv[1] : L"";
    std::wstring srcDir = DirOf(self);

    if (mode == L"--install-elevated" && argc > 2) {
        std::wstring err;
        return Install(argv[2], argc > 3 ? argv[3] : srcDir, &err) == Result::Ok ? 0 : 1;
    }
    if (mode == L"--uninstall-elevated" && argc > 2) { Uninstall(argv[2]); return 0; }

    std::wstring root = FindGameRoot();
    if (mode == L"--relaunch" && argc > 2) {
        // In-game updater: wait for the old game process, refresh Launch_Game.exe, start again through Steam.
        DWORD pid = (DWORD)_wtoi(argv[2]);
        HANDLE h = OpenProcess(SYNCHRONIZE, FALSE, pid);
        if (h) { WaitForSingleObject(h, 30000); CloseHandle(h); }
        Sleep(1000);
        if (root.empty()) root = DirOf(srcDir);
        std::wstring err;
        if (Install(root, srcDir, &err) == Result::AccessDenied)
            RunElevated(L"--install-elevated " + Quote(root) + L" " + Quote(srcDir));
        StartThroughSteam();
        return 0;
    }
    if (root.empty()) {
        // Not found through Steam's library list: ask once for the game folder.
        wchar_t file[MAX_PATH] = L"Launch_Game.exe";
        OPENFILENAMEW ofn{}; ofn.lStructSize = sizeof ofn; ofn.lpstrFile = file; ofn.nMaxFile = MAX_PATH;
        ofn.lpstrFilter = L"Bleeding Edge (Launch_Game.exe)\0Launch_Game.exe\0";
        ofn.lpstrTitle = L"Where is Bleeding Edge installed?"; ofn.Flags = OFN_FILEMUSTEXIST;
        if (!GetOpenFileNameW(&ofn)) return 1;
        root = DirOf(file);
        if (!IsFile(root + kGameRel)) { Message(L"That folder doesn't contain Bleeding Edge.", MB_ICONERROR); return 1; }
    }
    if (mode == L"--uninstall") {
        Uninstall(root);
        if (IsFile(root + L"\\BE1v1\\be1v1.dll")) RunElevated(L"--uninstall-elevated " + Quote(root));
        Message(L"The mod has been removed. Bleeding Edge is back to normal.");
        return 0;
    }
    if (GamePid()) { Message(L"Close Bleeding Edge first, then run this again.", MB_ICONWARNING); return 1; }
    std::wstring err;
    Result r = Install(root, srcDir, &err);
    if (r == Result::AccessDenied && !RunElevated(L"--install-elevated " + Quote(root) + L" " + Quote(srcDir))) r = Result::Failed;
    else if (r == Result::AccessDenied) r = Result::Ok;
    if (r != Result::Ok) { Message(L"Installation failed: " + err, MB_ICONERROR); return 1; }
    if (!SteamRunning()) {
        Message(L"Installed. Start Steam and play Bleeding Edge as usual; the mod loads by itself.");
        return 0;
    }
    StartThroughSteam();
    return 0;
}
