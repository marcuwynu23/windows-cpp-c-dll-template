#include <windows.h>

#include <cstdio>

using HelloFn = void (*)();
using PrintNumFn = void (*)(int);

int main() {
    HMODULE dll = LoadLibraryW(L"bin\\lib.dll");
    if (!dll) {
        std::fprintf(stderr, "LoadLibrary failed: %lu\n", GetLastError());
        return 1;
    }

    auto hello = reinterpret_cast<HelloFn>(GetProcAddress(dll, "hello"));
    auto printNumber = reinterpret_cast<PrintNumFn>(GetProcAddress(dll, "printNumber"));
    if (!hello || !printNumber) {
        std::fprintf(stderr, "GetProcAddress failed: %lu\n", GetLastError());
        FreeLibrary(dll);
        return 1;
    }

    hello();
    printNumber(23);

    FreeLibrary(dll);
    return 0;
}
