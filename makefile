# Windows DLL sample — LLVM Clang (not MinGW)
CXX      := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

DLL      := bin/lib.dll
TEST     := bin/test.exe
SRC      := $(wildcard src/*.cpp)

.PHONY: all clean test

all: $(DLL)

$(DLL): $(SRC) include/lib.h
	$(CXX) $(CXXFLAGS) -shared -DBUILD_DLL -o $@ $(SRC)

$(TEST): bin/test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

test: $(DLL) $(TEST)
	$(TEST)

clean:
	-del /Q "$(DLL)" "$(TEST)" bin\lib.lib bin\lib.exp 2>nul
