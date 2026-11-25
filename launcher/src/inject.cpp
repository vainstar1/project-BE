// Starts the game suspended and loads be1v1.dll before any game code runs (early-bird APC on the main thread).
#include <windows.h>
#include <string>
#include "inject.h"

// Bleeding Edge's Steam app id. Steam normally hands it to the game; when we start the game ourselves Steamworks
// needs it from the SteamAppId/SteamGameId environment variables or steam_appid.txt, otherwise Steam networking
// doesn't start (and the game asks Steam to relaunch it).
static const wchar_t* kAppId = L"1189800";

static void EnsureSteamAppId(const std::wstring& dir) {
    SetEnvironmentVariableW(L"SteamAppId", kAppId);   // inherited by the game process
    SetEnvironmentVariableW(L"SteamGameId", kAppId);
    std::wstring f = dir + L"\\steam_appid.txt";
    if (GetFileAttributesW(f.c_str()) != INVALID_FILE_ATTRIBUTES) return;
    HANDLE h = CreateFileW(f.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) return;   // read-only install: the environment variables still cover it
    DWORD w; WriteFile(h, "1189800", 7, &w, nullptr); CloseHandle(h);
}

bool LaunchWithDll(const std::wstring& exe, const std::wstring& args, const std::wstring& dll, PROCESS_INFORMATION* outPi, std::wstring* err) {
    std::wstring dir = exe.substr(0, exe.find_last_of(L"\\/"));
    std::wstring cmd = L"\"" + exe + L"\" " + args;
    EnsureSteamAppId(dir);
    STARTUPINFOW si{}; si.cb = sizeof si;
    PROCESS_INFORMATION pi{};
    if (!CreateProcessW(exe.c_str(), &cmd[0], nullptr, nullptr, FALSE, CREATE_SUSPENDED, nullptr, dir.c_str(), &si, &pi)) {
        *err = L"CreateProcess failed (" + std::to_wstring(GetLastError()) + L")"; return false;
    }
    size_t bytes = (dll.size() + 1) * sizeof(wchar_t);
    void* mem = VirtualAllocEx(pi.hProcess, nullptr, bytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!mem || !WriteProcessMemory(pi.hProcess, mem, dll.c_str(), bytes, nullptr)) {
        *err = L"could not write DLL path"; TerminateProcess(pi.hProcess, 1); return false;
    }
    auto loadLib = (PAPCFUNC)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "LoadLibraryW");
    if (!QueueUserAPC(loadLib, pi.hThread, (ULONG_PTR)mem)) {
        *err = L"QueueUserAPC failed"; TerminateProcess(pi.hProcess, 1); return false;
    }
    ResumeThread(pi.hThread);
    *outPi = pi;
    return true;
}
