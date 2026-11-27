// OS-level conveniences: skip the intro videos and auto-accept the EasyAntiCheat warning box.
#include <windows.h>
#include <cwchar>
#include <cstdio>
#include <cstring>
#include "MinHook.h"
#include "ue.h"
#include "uobj.h"

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
    else if (!strcmp(cmd, "netid")) {
        for (uo::UObject* ps : uo::FindAll(uo::FindClass(L"PlayerState"))) {
            uint8_t* w = ps + 0x3f8;
            void** id = F<void**>(w, 8);
            void* ctl = F<void*>(w, 0x10);
            Log("dev: %ls uid wrapper vt=%llx obj=%p ctl=%p", uo::Name(ps).c_str(), (unsigned long long)(F<uintptr_t>(w, 0) - gBase + 0x140000000ull), id, ctl);
            if (id) Log("dev:   id vt=%llx q1=%llx q2=%llx ctl vt=%llx refs=%x/%x", (unsigned long long)((uintptr_t)id[0] - gBase + 0x140000000ull), (unsigned long long)(uintptr_t)id[1],
                        (unsigned long long)(uintptr_t)id[2], ctl ? (unsigned long long)(F<uintptr_t>(ctl, 0) - gBase + 0x140000000ull) : 0, ctl ? F<int32_t>(ctl, 8) : 0, ctl ? F<int32_t>(ctl, 12) : 0);
        }
    }
    else if (!strcmp(cmd, "noafk")) {
        // Test runs: no idle kick in this match (posted-key tests leave a player still for minutes).
        for (uo::UObject* m : uo::FindAll(uo::FindClass(L"MBAFKManager"))) { F<float>(m, 0x28) = 1.0e9f; F<float>(m, 0x2c) = 1.0e9f; Log("dev: idle kick off (%ls)", uo::Name(m).c_str()); }
    }
    else if (!strcmp(cmd, "testbinds")) {
        // Test runs only (not saved): attacks on spare keys, so posted key presses can fight (posted mouse clicks
        // don't reach the game). F13 melee, F14 ability 1, F15 ability 2, F16 ability 3.
        uo::UObject* is = uo::FindObjectPath(L"/Script/Engine.Default__InputSettings");
        const wchar_t* map[][2] = { { L"MeleeAttack", L"F13" }, { L"SpecialAbility1", L"F14" }, { L"SpecialAbility2", L"F15" }, { L"SpecialAbility3", L"F16" } };
        for (auto& m : map) {
            uo::Call c(is, L"AddActionMapping");
            int o = c.off(L"KeyMapping");
            if (!c.ok() || o < 0) { Log("dev: AddActionMapping missing"); return; }
            F<FName>(c.buf.data() + o, 0) = uo::MakeName(m[0]);
            F<FName>(c.buf.data() + o, 0x10) = uo::MakeName(m[1]);
            c.set<bool>(L"bForceRebuildKeymaps", true).run();
        }
        Log("dev: test key bindings F13-F16 added");
    }
}
