// Developer launcher used by the test harness: devlaunch.exe <game exe> <dll> [game args...]
// Prints the new process id.
#include <windows.h>
#include <cstdio>
#include <string>
#include "inject.h"

int wmain(int argc, wchar_t** argv) {
    if (argc < 3) { fwprintf(stderr, L"usage: devlaunch <exe> <dll> [args...]\n"); return 2; }
    std::wstring args;
    for (int i = 3; i < argc; i++) { if (i > 3) args += L" "; args += argv[i]; }
    wchar_t full[MAX_PATH]; GetFullPathNameW(argv[2], MAX_PATH, full, nullptr);
    PROCESS_INFORMATION pi; std::wstring err;
    if (!LaunchWithDll(argv[1], args, full, &pi, &err)) { fwprintf(stderr, L"%ls\n", err.c_str()); return 1; }
    wprintf(L"%lu\n", pi.dwProcessId);
    return 0;
}
