#!/bin/sh
# Builds be1v1.dll with the winlibs MinGW toolchain.
set -e
cd "$(dirname "$0")"
TC="/c/Users/andre/Downloads/winlibs-x86_64-posix-seh-gcc-14.2.0-llvm-19.1.1-mingw-w64ucrt-12.0.0-r2/mingw64/bin"
export PATH="$TC:$PATH"
mkdir -p ../build
MH=third_party/minhook
gcc -c -O2 -I$MH/include $MH/src/hook.c $MH/src/buffer.c $MH/src/trampoline.c $MH/src/hde/hde64.c
g++ -std=c++17 -O2 -shared -static -s -Wall -Wno-unused-function -I$MH/include \
    src/*.cpp hook.o buffer.o trampoline.o hde64.o -o ../build/be1v1.dll -lws2_32 -lwinhttp
rm -f *.o
echo built ../build/be1v1.dll
