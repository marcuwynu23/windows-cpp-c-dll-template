#ifndef LIB_H
#define LIB_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) && defined(BUILD_DLL)
#  define LIB_API __declspec(dllexport)
#elif defined(_WIN32)
#  define LIB_API __declspec(dllimport)
#else
#  define LIB_API
#endif

LIB_API void hello(void);
LIB_API void printNumber(int number);

#ifdef __cplusplus
}
#endif

#endif
