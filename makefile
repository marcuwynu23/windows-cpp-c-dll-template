BIN=bin/lib.dll
all:
	c++ -I "include" -shared -o $(BIN)  $(wildcard src/*.cpp)

test:
	c++ bin/test.cpp -o bin/test.exe


