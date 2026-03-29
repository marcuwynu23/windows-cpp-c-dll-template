# Windows DLL sample — LLVM Clang (not MinGW)
CC       := clang
CXX      := clang++
CFLAGS   := -std=c11 -Wall -Wextra
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

DLL      := bin/lib.dll
TEST     := bin/test.exe
TEST_C   := bin/test_c.exe
SRC      := $(wildcard src/*.cpp)

.PHONY: all clean test test-c

all: $(DLL)

$(DLL): $(SRC) include/lib.h
	$(CXX) $(CXXFLAGS) -shared -DBUILD_DLL -o $@ $(SRC)

$(TEST): bin/test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(TEST_C): bin/test.c
	$(CC) $(CFLAGS) -o $@ $<

test: $(DLL) $(TEST)
	$(TEST)

test-c: $(DLL) $(TEST_C)
	$(TEST_C)

clean:
	-del /Q "$(DLL)" "$(TEST)" "$(TEST_C)" bin\lib.lib bin\lib.exp 2>nul
