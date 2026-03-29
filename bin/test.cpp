#include <windows.h>

#include <cwchar>
#include <cstdio>

using HelloFn = void (*)();
using PrintNumFn = void (*)(int);

static bool append_dll_path(wchar_t* path, size_t cap) {
    wchar_t* slash = std::wcsrchr(path, L'\\');
    if (!slash) {
        return false;
    }
    slash[1] = L'\0';
    return wcscat_s(path, cap, L"lib.dll") == 0;
}

int main() {
    wchar_t path[MAX_PATH];
    DWORD n = GetModuleFileNameW(nullptr, path, MAX_PATH);
    if (!n || n >= MAX_PATH || !append_dll_path(path, MAX_PATH)) {
        std::fprintf(stderr, "Could not resolve path to lib.dll\n");
        return 1;
    }

    HMODULE dll = LoadLibraryW(path);
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
