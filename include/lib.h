#ifndef __DLLEXPORT_H__
#define __DLLEXPORT_H__
#ifdef __cplusplus

extern "C"{
#endif

#ifdef BUILD_DLL
    #define DLL_IMPORT __declspec(dllexport)
#else
    #define DLL_IMPORT __declspec(dllimport)
#endif



//for export functions initiation
void hello(void);
void printNumber(int number);


#ifdef __cplusplus
}
#endif
#endif 

 
