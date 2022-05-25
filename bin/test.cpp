#include <windows.h>


typedef void (*pHelloFunc)(); 


int main(int argc, char const *argv[])
{	
	HMODULE  dll  = LoadLibrary("bin/lib.dll");    
	pHelloFunc  hello = (pHelloFunc) GetProcAddress(dll, "hello"); 
	hello();
	
	return 0;
}