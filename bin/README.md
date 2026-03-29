# Loading `lib.dll` from the `bin/` folder

This folder is a **reference** for how to call the DLL’s exported symbols (`hello`, `printNumber`) from several languages. The DLL is built from the repo root (`make` / `make all`); the output is **`bin/lib.dll`**.

All loaders here resolve **`lib.dll` next to the loader** (same directory as the executable or script), so the current working directory does not matter.

---

## C (LLVM Clang)

`test.c` uses the Windows API (`LoadLibraryW`, `GetProcAddress`, `FreeLibrary`).

**Build from the repo root:**

```bash
clang -std=c11 -Wall -Wextra -o bin/test_c.exe bin/test.c
```

**Or use Make:**

```bash
make test-c
```

**Run:** `bin\test_c.exe` (double-click or run from any directory).

---

## C++ (LLVM Clang)

`test.cpp` is the same idea as `test.c`, using the C++ standard library for wide-character helpers.

**Build from the repo root:**

```bash
clang++ -std=c++17 -Wall -Wextra -o bin/test.exe bin/test.cpp
```

**Or use Make:**

```bash
make test
```

---

## Python 3

`test.py` uses the standard library only **`ctypes`** (`CDLL` = cdecl, matching the C exports).

```bash
python bin/test.py
```

On Windows, if `python` is not on `PATH`:

```bash
py -3 bin/test.py
```

---

## Node.js (JavaScript)

`test.js` uses **[koffi](https://github.com/Koromix/koffi)** to load the DLL and bind functions.

```bash
cd bin
npm install
node test.js
```

`package.json` in this folder lists the `koffi` dependency.

---

## Java

`test.java` uses the standard **Foreign Function & Memory (FFM)** API (`java.lang.foreign`), available without extra JARs from **JDK 22** onward. No Maven classpath and no JNA.

On **JDK 24+**, always pass **`--enable-native-access=ALL-UNNAMED`** when running. Without it, `java test.java` still works but prints warnings about restricted native access; with the flag, output is clean and future JDKs will not block `SymbolLookup.libraryLookup`.

From **`bin/`** (where `lib.dll` lives):

```bash
javac test.java
java --enable-native-access=ALL-UNNAMED test
```

Or compile and run in one step:

```bash
java --enable-native-access=ALL-UNNAMED test.java
```

**Optional:** set once per shell so you can type `java test.java` without the flag:

- **cmd.exe:** `set JAVA_TOOL_OPTIONS=--enable-native-access=ALL-UNNAMED`
- **PowerShell:** `$env:JAVA_TOOL_OPTIONS="--enable-native-access=ALL-UNNAMED"`

---

## Quick reference

| File | Language | Tool / library |
|------|----------|----------------|
| `test.c` | C | Clang, Windows `kernel32` / `LoadLibraryW` |
| `test.cpp` | C++ | Clang++, same Windows APIs |
| `test.py` | Python 3 | `ctypes` |
| `test.js` | JavaScript (Node) | `koffi` |
| `test.java` | Java | JDK 22+ FFM (`java.lang.foreign`) |

---

## Exported API (from `include/lib.h`)

The DLL is built with `extern "C"` and `__declspec(dllexport)` so names are stable for `GetProcAddress` and FFI:

```text
void hello(void);
void printNumber(int number);
```
