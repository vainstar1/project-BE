#!/bin/sh
# Builds the launcher executables with the winlibs MinGW toolchain.
set -e
cd "$(dirname "$0")"
TC="/c/Users/andre/Downloads/winlibs-x86_64-posix-seh-gcc-14.2.0-llvm-19.1.1-mingw-w64ucrt-12.0.0-r2/mingw64/bin"
export PATH="$TC:$PATH"
mkdir -p ../build
g++ -std=c++17 -O2 -static -s -municode src/devlaunch.cpp src/inject.cpp -o ../build/devlaunch.exe
windres -i res/app.rc -o res.o --include-dir res
g++ -std=c++17 -O2 -static -s -municode -mwindows src/main.cpp src/inject.cpp res.o -o ../build/BE1v1.exe -lcomdlg32 -lshell32
rm -f res.o
echo built ../build/BE1v1.exe ../build/devlaunch.exe
