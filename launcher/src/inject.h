#pragma once
#include <windows.h>
#include <string>

bool LaunchWithDll(const std::wstring& exe, const std::wstring& args, const std::wstring& dll, PROCESS_INFORMATION* outPi, std::wstring* err);
