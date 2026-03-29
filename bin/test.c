#include <windows.h>

#include <stdio.h>
#include <wchar.h>

typedef void (*HelloFn)(void);
typedef void (*PrintNumFn)(int);

static int append_dll_path(wchar_t* path, size_t cap) {
    wchar_t* slash = wcsrchr(path, L'\\');
    if (!slash) {
        return 0;
    }
    slash[1] = L'\0';
    return wcscat_s(path, cap, L"lib.dll") == 0;
}

int main(void) {
    wchar_t path[MAX_PATH];
    DWORD n = GetModuleFileNameW(NULL, path, MAX_PATH);
    if (!n || n >= MAX_PATH || !append_dll_path(path, MAX_PATH)) {
        fprintf(stderr, "Could not resolve path to lib.dll\n");
        return 1;
    }

    HMODULE dll = LoadLibraryW(path);
    if (!dll) {
        fprintf(stderr, "LoadLibrary failed: %lu\n", GetLastError());
        return 1;
    }

    HelloFn hello = (HelloFn)(void*)GetProcAddress(dll, "hello");
    PrintNumFn printNumber = (PrintNumFn)(void*)GetProcAddress(dll, "printNumber");
    if (!hello || !printNumber) {
        fprintf(stderr, "GetProcAddress failed: %lu\n", GetLastError());
        FreeLibrary(dll);
        return 1;
    }

    hello();
    printNumber(23);

    FreeLibrary(dll);
    return 0;
}
