// OS-level conveniences: skip the intro videos and auto-accept the EasyAntiCheat warning box.
#include <windows.h>
#include <cwchar>
#include <cstdio>
#include <cstring>
#include "MinHook.h"
#include "ue.h"

namespace {
const wchar_t* kSkipMovies[] = { L"NT_IntroVideo", L"XboxGamesStudios_Logo", L"Playfab_Simplygon_Logos", L"UE4_Startup_Moving_Logo",
                                 L"UE4_Moving_Logo", L"OpeningCine" };

bool IsSkippedMovie(const wchar_t* path) {
    if (!path || !wcsstr(path, L"Movies")) return false;
    for (auto m : kSkipMovies) if (wcsstr(path, m)) return true;
    return false;
}

using CreateFileW_t = HANDLE(WINAPI*)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
CreateFileW_t oCreateFileW;
HANDLE WINAPI hkCreateFileW(LPCWSTR n, DWORD a, DWORD s, LPSECURITY_ATTRIBUTES sa, DWORD c, DWORD f, HANDLE t) {
    if (IsSkippedMovie(n)) { Log("skipping movie %ls", n); SetLastError(ERROR_FILE_NOT_FOUND); return INVALID_HANDLE_VALUE; }
    return oCreateFileW(n, a, s, sa, c, f, t);
}
using CreateFile2_t = HANDLE(WINAPI*)(LPCWSTR, DWORD, DWORD, DWORD, void*);
CreateFile2_t oCreateFile2;
HANDLE WINAPI hkCreateFile2(LPCWSTR n, DWORD a, DWORD s, DWORD c, void* p) {
    if (IsSkippedMovie(n)) { Log("skipping movie %ls", n); SetLastError(ERROR_FILE_NOT_FOUND); return INVALID_HANDLE_VALUE; }
    return oCreateFile2(n, a, s, c, p);
}

using MessageBoxW_t = int(WINAPI*)(HWND, LPCWSTR, LPCWSTR, UINT);
MessageBoxW_t oMessageBoxW;
int WINAPI hkMessageBoxW(HWND h, LPCWSTR text, LPCWSTR cap, UINT type) {
    if (text && wcsstr(text, L"EasyAntiCheat")) { Log("auto-accepted EAC box"); return IDOK; }
    return oMessageBoxW(h, text, cap, type);
}
using MessageBoxA_t = int(WINAPI*)(HWND, LPCSTR, LPCSTR, UINT);
MessageBoxA_t oMessageBoxA;
int WINAPI hkMessageBoxA(HWND h, LPCSTR text, LPCSTR cap, UINT type) {
    if (text && strstr(text, "EasyAntiCheat")) { Log("auto-accepted EAC box"); return IDOK; }
    return oMessageBoxA(h, text, cap, type);
}

// Developer testing: a fake cursor position (client coordinates of the game window) so posted mouse messages land
// where the harness wants without moving the user's real cursor. Off unless a dev command turns it on.
bool gFakeCursor;
POINT gFakePos;
using GetCursorPos_t = BOOL(WINAPI*)(LPPOINT);
GetCursorPos_t oGetCursorPos;
HWND GameWindow() {
    struct S { DWORD pid; HWND h; } s{ GetCurrentProcessId(), nullptr };
    EnumWindows([](HWND h, LPARAM l) -> BOOL {
        auto* s = (S*)l; DWORD pid; GetWindowThreadProcessId(h, &pid);
        wchar_t c[64]; GetClassNameW(h, c, 64);
        if (pid == s->pid && !wcscmp(c, L"UnrealWindow") && IsWindowVisible(h)) { s->h = h; return FALSE; }
        return TRUE;
    }, (LPARAM)&s);
    return s.h;
}
BOOL WINAPI hkGetCursorPos(LPPOINT p) {
    if (gFakeCursor && p) { *p = gFakePos; HWND h = GameWindow(); if (h) ClientToScreen(h, p); return TRUE; }
    return oGetCursorPos(p);
}

template <class T> void HookApi(const wchar_t* mod, const char* name, void* det, T* orig) {
    HMODULE m = GetModuleHandleW(mod);
    if (!m) m = LoadLibraryW(mod);
    void* p = m ? (void*)GetProcAddress(m, name) : nullptr;
    if (!p) { Log("api %s not found", name); return; }
    if (MH_CreateHook(p, det, (void**)orig) != MH_OK) { Log("hook %s failed", name); return; }
    MH_EnableHook(p);
}
}  // namespace

void InstallSys() {
    // FOnlineSubsystemSteam::InitSteamworksClient (0x1408043a0) calls SteamAPI_RestartAppIfNecessary when the game
    // wasn't started by Steam; Steam then kills us and relaunches the game *without* this DLL (seen as Steam's
    // "alternate launch options" prompt). Skip that call: "je" -> "jmp" at 0x1408043bb.
    uint8_t* p = (uint8_t*)VA(0x1408043bb);
    if (p[0] == 0x74 && p[1] == 0x16) { uint8_t j = 0xEB; PatchBytes(p, &j, 1); Log("steam-relaunch patch: 1"); }
    else Log("steam-relaunch patch: bytes mismatch");

    HookApi(L"kernelbase.dll", "CreateFileW", (void*)&hkCreateFileW, &oCreateFileW);
    HookApi(L"kernelbase.dll", "CreateFile2", (void*)&hkCreateFile2, &oCreateFile2);
    HookApi(L"user32.dll", "MessageBoxW", (void*)&hkMessageBoxW, &oMessageBoxW);
    HookApi(L"user32.dll", "MessageBoxA", (void*)&hkMessageBoxA, &oMessageBoxA);
    HookApi(L"user32.dll", "GetCursorPos", (void*)&hkGetCursorPos, &oGetCursorPos);
    Log("sys hooks installed");
}

void SysDevCommand(const char* cmd) {
    int x, y;
    if (sscanf(cmd, "cursor %d %d", &x, &y) == 2) { gFakePos = { x, y }; gFakeCursor = true; Log("dev: fake cursor %d,%d", x, y); }
    else if (!strcmp(cmd, "cursor off")) gFakeCursor = false;
}
