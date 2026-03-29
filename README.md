# windows-cpp-c-dll-template

Minimal **project template** for a **Windows DLL** in **C or C++**: shared library build with **LLVM Clang**, `extern "C"` exports for a stable ABI, and a small loader that uses `LoadLibrary` / `GetProcAddress`.

Fork or copy this repo, rename the project, then replace `hello` / `printNumber` with your API.

Other good names: `cpp-windows-dll-template`, `win32-dll-library-starter`.

## Requirements

- [LLVM](https://llvm.org/) — `clang++` on `PATH` (C++ sources); use `clang` for plain C if you add `.c` files
- `make` (e.g. from Git for Windows)
- The loader looks for `lib.dll` **next to the executable** (works from any working directory)

## Loaders (C, C++, Python, Node, Java)

See **[bin/README.md](bin/README.md)** for how to build and run **`test.c`**, **`test.cpp`**, **`test.py`**, **`test.js`**, and **`test.java`** against `lib.dll`.

Quick checks from the repo root: `make test` (C++), `make test-c` (C).
