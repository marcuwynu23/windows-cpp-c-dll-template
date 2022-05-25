BIN=bin/lib.dll

#compile src to DLL
all:
	c++ -I "include" -shared -o $(BIN)  $(wildcard src/*.cpp)

#test DLL
test:
	c++ bin/test.cpp -o bin/test.exe
	bin/test.exe

