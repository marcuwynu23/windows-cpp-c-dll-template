#!/usr/bin/env python3
"""Load lib.dll (same folder as this script) via ctypes."""

import ctypes
import os
import sys

_dir = os.path.dirname(os.path.abspath(__file__))
_dll_path = os.path.join(_dir, "lib.dll")

try:
    lib = ctypes.CDLL(_dll_path)
except OSError as e:
    print(f"LoadLibrary failed: {e}", file=sys.stderr)
    sys.exit(1)

lib.hello.argtypes = ()
lib.hello.restype = None
lib.printNumber.argtypes = (ctypes.c_int,)
lib.printNumber.restype = None

lib.hello()
lib.printNumber(23)
