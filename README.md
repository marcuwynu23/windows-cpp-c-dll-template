# windows-cpp-c-dll-template

Minimal **project template** for a **Windows DLL** in **C or C++**: shared library build with **LLVM Clang**, `extern "C"` exports for a stable ABI, and a small loader that uses `LoadLibrary` / `GetProcAddress`.

Fork or copy this repo, rename the project, then replace `hello` / `printNumber` with your API.

Other good names: `cpp-windows-dll-template`, `win32-dll-library-starter`.

## Requirements

- [LLVM](https://llvm.org/) — `clang++` on `PATH` (C++ sources); use `clang` for plain C if you add `.c` files
- `make` (e.g. from Git for Windows)
- Run `make test` from the repo root so `bin\lib.dll` resolves correctly
