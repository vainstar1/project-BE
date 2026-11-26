// be1v1: native host/join support for Bleeding Edge (Steam build, UE 4.20.3).
// Exe SHA-256 41ab697b4edd3061baff37568de6e9501427374a859b048b3595f29297bfd306, image base 0x140000000.
#include <windows.h>
#include <cstdint>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include "MinHook.h"
#include "ue.h"
#include "uobj.h"
#include "mod.h"
#include <string>
#include <vector>
#include <algorithm>

HMODULE gSelf;
uintptr_t gBase;
static FILE* gLog;
static CRITICAL_SECTION gLogCs;

void Log(const char* fmt, ...) {
    EnterCriticalSection(&gLogCs);
    if (gLog) {
        SYSTEMTIME t; GetLocalTime(&t);
        fprintf(gLog, "%02d:%02d:%02d.%03d ", t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
        va_list a; va_start(a, fmt); vfprintf(gLog, fmt, a); va_end(a);
        fputc('\n', gLog); fflush(gLog);
    }
    LeaveCriticalSection(&gLogCs);
}

bool PatchBytes(void* dst, const void* src, size_t n) {
    DWORD old;
    if (!VirtualProtect(dst, n, PAGE_EXECUTE_READWRITE, &old)) return false;
    memcpy(dst, src, n);
    VirtualProtect(dst, n, old, &old);
    FlushInstructionCache(GetCurrentProcess(), dst, n);
    return true;
}

// Allocates a page within +-2GB of `near` for rel32 thunks.
static uint8_t* AllocNear(uintptr_t near_) {
    SYSTEM_INFO si; GetSystemInfo(&si);
    uintptr_t gran = si.dwAllocationGranularity;
    for (uintptr_t a = (near_ & ~(gran - 1)) - gran; a > near_ - 0x7FF00000ull; a -= gran) {
        void* p = VirtualAlloc((void*)a, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (p) return (uint8_t*)p;
    }
    return nullptr;
}
static uint8_t* gThunks; static size_t gThunkUsed;

// Redirects an E8 call at `site` (whose current target must be `expect`) to `fn`.
bool PatchCall(uintptr_t siteVa, uintptr_t expectVa, void* fn) {
    uint8_t* site = (uint8_t*)VA(siteVa);
    if (site[0] != 0xE8) { Log("PatchCall %llx: not a call", (unsigned long long)siteVa); return false; }
    int32_t rel = *(int32_t*)(site + 1);
    if ((uintptr_t)(site + 5 + rel) != VA(expectVa)) { Log("PatchCall %llx: unexpected target", (unsigned long long)siteVa); return false; }
    if (!gThunks) gThunks = AllocNear(gBase);
    uint8_t* th = gThunks + gThunkUsed; gThunkUsed += 16;
    th[0] = 0xFF; th[1] = 0x25; *(int32_t*)(th + 2) = 0; *(void**)(th + 6) = fn;   // jmp [rip+0]; dq fn
    uint8_t patch[5] = { 0xE8 }; *(int32_t*)(patch + 1) = (int32_t)(th - (site + 5));
    return PatchBytes(site, patch, 5);
}

bool PatchVtable(uintptr_t vtableVa, int slot, void* fn, void** orig) {
    void** p = (void**)VA(vtableVa) + slot;
    if (orig) *orig = *p;
    return PatchBytes(p, &fn, sizeof(fn));
}

static const char* ModOf(uintptr_t a, uintptr_t* rel) {
    static char name[MAX_PATH];
    HMODULE m = nullptr;
    if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)a, &m) && m) {
        if ((uintptr_t)m == gBase) { *rel = a - gBase + 0x140000000ull; return "game"; }
        if (m == gSelf) { *rel = a - (uintptr_t)m; return "be1v1"; }
        *rel = a - (uintptr_t)m;
        char full[MAX_PATH]; GetModuleFileNameA(m, full, MAX_PATH);
        const char* s = strrchr(full, '\\'); snprintf(name, sizeof name, "%s", s ? s + 1 : full);
        return name;
    }
    *rel = a; return "?";
}

// Logs fatal-looking exceptions (first chance) with a short stack scan, then lets the game handle them.
static LONG CALLBACK CrashLogger(EXCEPTION_POINTERS* ep) {
    DWORD code = ep->ExceptionRecord->ExceptionCode;
    if (code != EXCEPTION_ACCESS_VIOLATION && code != EXCEPTION_ILLEGAL_INSTRUCTION && code != EXCEPTION_STACK_OVERFLOW &&
        code != EXCEPTION_INT_DIVIDE_BY_ZERO && code != 0xC0000409) return EXCEPTION_CONTINUE_SEARCH;
    static volatile LONG n; if (InterlockedIncrement(&n) > 8) return EXCEPTION_CONTINUE_SEARCH;
    CONTEXT* c = ep->ContextRecord; uintptr_t rel;
    const char* m = ModOf(c->Rip, &rel);
    Log("EXCEPTION %08lx at %s+%llx addr=%llx rcx=%llx rdx=%llx r8=%llx rax=%llx", code, m, (unsigned long long)rel,
        (unsigned long long)ep->ExceptionRecord->ExceptionInformation[1], (unsigned long long)c->Rcx, (unsigned long long)c->Rdx,
        (unsigned long long)c->R8, (unsigned long long)c->Rax);
    uint8_t code16[16] = {};
    if (ReadProcessMemory(GetCurrentProcess(), (void*)c->Rip, code16, 16, nullptr)) {
        char hex[64] = {}; for (int i = 0; i < 16; i++) sprintf(hex + i * 3, "%02x ", code16[i]);
        Log("   rip=%llx bytes: %s", (unsigned long long)c->Rip, hex);
    }
    uintptr_t* sp = (uintptr_t*)c->Rsp;
    int shown = 0;
    for (int i = 0; i < 400 && shown < 16; i++) {
        uintptr_t v; if (!ReadProcessMemory(GetCurrentProcess(), sp + i, &v, 8, nullptr)) break;
        const char* mm = ModOf(v, &rel);
        bool game = !strcmp(mm, "game"), self = !strcmp(mm, "be1v1");
        if (game && (rel < 0x140001000 || rel > 0x143300000)) continue;
        if (game || self) { Log("   stack %s+%llx", mm, (unsigned long long)rel); shown++; }
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

void InstallNet();   // net.cpp
void InstallRepl();  // repl.cpp
void InstallSys();   // sys.cpp
void InstallGame();  // game.cpp
void LobbyDevCommand(const char* cmd);   // lobby.cpp
void SysDevCommand(const char* cmd);     // sys.cpp
void GameTeamsTick();                    // game.cpp

static char gDllDir[MAX_PATH];
static bool gUoReady;

std::wstring ModDir() { wchar_t w[MAX_PATH]; MultiByteToWideChar(CP_ACP, 0, gDllDir, -1, w, MAX_PATH); return w; }
std::wstring Utf8ToWide(const std::string& s) {
    if (s.empty()) return L"";
    int n = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
    std::wstring w(n, L'\0'); MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), &w[0], n); return w;
}
std::string WideToUtf8(const std::wstring& w) {
    if (w.empty()) return "";
    int n = WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    std::string s(n, '\0'); WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), &s[0], n, nullptr, nullptr); return s;
}

// Developer command channel: <dll dir>\\be1v1-cmd-<pid>.txt, polled on the game thread.
static void DevPoll() {
    char p[MAX_PATH]; snprintf(p, sizeof p, "%sbe1v1-cmd-%lu.txt", gDllDir, GetCurrentProcessId());
    FILE* f = fopen(p, "rb"); if (!f) return;
    char buf[512] = {}; fread(buf, 1, sizeof buf - 1, f); fclose(f); DeleteFileA(p);
    for (char* e = buf + strlen(buf); e > buf && (e[-1] == '\n' || e[-1] == '\r' || e[-1] == ' '); ) *--e = 0;
    Log("dev cmd: %s", buf);
    if (!strncmp(buf, "lobby ", 6)) LobbyDevCommand(buf + 6);
    else if (!strncmp(buf, "ui ", 3)) ui::DevCommand(buf + 3);
    else SysDevCommand(buf);
}

// Called once per frame on the game thread (from the UEngine::TickWorldTravel hook).
void GameTick(float dt) {
    static float acc;
    if (!gUoReady) { gUoReady = uo::Init(); if (!gUoReady) return; }
    acc += dt;
    if (acc > 0.5f) { acc = 0; DevPoll(); }
    uo::IndexStep(12000);
    // Each part is timed; slow frames are logged (rate-limited) so performance problems show up in user logs.
    static LARGE_INTEGER freq; if (!freq.QuadPart) QueryPerformanceFrequency(&freq);
    LARGE_INTEGER t[8]; int n = 0;
    QueryPerformanceCounter(&t[n++]);
    ui::Tick(dt); ui::FastTick();      QueryPerformanceCounter(&t[n++]);
    lobby::Tick(dt);                    QueryPerformanceCounter(&t[n++]);
    settings::Tick();                   QueryPerformanceCounter(&t[n++]);
    rules::Tick();                      QueryPerformanceCounter(&t[n++]);
    GameTeamsTick();                    QueryPerformanceCounter(&t[n++]);
    update::Tick(dt);                   QueryPerformanceCounter(&t[n++]);
    double total = (t[n - 1].QuadPart - t[0].QuadPart) * 1000.0 / freq.QuadPart;
    static DWORD lastSlow; static int slowCount;
    if (total > 12.0) {
        slowCount++;
        if (GetTickCount() - lastSlow > 5000) {
            lastSlow = GetTickCount();
            auto ms = [&](int i) { return (t[i + 1].QuadPart - t[i].QuadPart) * 1000.0 / freq.QuadPart; };
            Log("perf: slow tick %.1f ms (ui %.1f lobby %.1f settings %.1f rules %.1f teams %.1f update %.1f), %d slow ticks",
                total, ms(0), ms(1), ms(2), ms(3), ms(4), ms(5), slowCount);
        }
    }
}

// Runs inside DllMain: the launcher loads us before the game's entry point, so everything must be in place now.
static void Init() {
    char path[MAX_PATH]; GetModuleFileNameA(gSelf, path, MAX_PATH);
    char* slash = strrchr(path, '\\'); if (slash) slash[1] = 0;
    strcpy(gDllDir, path);
    // Keep the 10 newest logs.
    {
        char pat[MAX_PATH]; snprintf(pat, sizeof pat, "%sbe1v1-*.log", path);
        std::vector<std::pair<uint64_t, std::string>> logs;
        WIN32_FIND_DATAA fd; HANDLE h = FindFirstFileA(pat, &fd);
        if (h != INVALID_HANDLE_VALUE) {
            do logs.push_back({ ((uint64_t)fd.ftLastWriteTime.dwHighDateTime << 32) | fd.ftLastWriteTime.dwLowDateTime, fd.cFileName });
            while (FindNextFileA(h, &fd));
            FindClose(h);
        }
        std::sort(logs.begin(), logs.end());
        for (size_t i = 0; i + 9 < logs.size(); i++) DeleteFileA((std::string(path) + logs[i].second).c_str());
    }
    char logPath[MAX_PATH]; snprintf(logPath, sizeof logPath, "%sbe1v1-%lu.log", path, GetCurrentProcessId());
    gLog = fopen(logPath, "a");
    gBase = (uintptr_t)GetModuleHandleW(nullptr);
    Log("be1v1 loaded, base=%p", (void*)gBase);
    // Build check: the Listen call site in UEngine::LoadMap must match.
    const uint8_t* p = (const uint8_t*)VA(0x1425e0537);
    if (p[0] != 0xE8 || (uintptr_t)(p + 5 + *(int32_t*)(p + 1)) != VA(0x1402ec800)) {
        Log("unsupported game build; doing nothing");
        return;
    }
    AddVectoredExceptionHandler(1, CrashLogger);
    MH_Initialize();
    InstallSys();
    InstallNet();
    InstallRepl();
    InstallGame();
    lobby::Install();
    rules::Install();
    ui::Install();
    update::Install();
    MH_EnableHook(MH_ALL_HOOKS);
    Log("hooks installed");
}

BOOL APIENTRY DllMain(HMODULE m, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        gSelf = m;
        InitializeCriticalSection(&gLogCs);
        DisableThreadLibraryCalls(m);
        Init();
    }
    return TRUE;
}
