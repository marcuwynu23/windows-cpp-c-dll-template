#include <windows.h>

//function pointers
typedef void (*pHelloFunc)(); 
typedef void (*pPrintNumFunc)(int number); 


int main(int argc, char const *argv[])
{	
	//loading DLL
	HMODULE  dll  = LoadLibrary("bin/lib.dll");    

	//clone function from DLL
	pHelloFunc  		hello = (pHelloFunc) GetProcAddress(dll, "hello"); 
	pPrintNumFunc  	printNumber = (pPrintNumFunc) GetProcAddress(dll, "printNumber");

	// calling function 
	hello();
	printNumber(23);
	
	return 0;
}