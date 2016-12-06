#ifndef BASEDEF_H
#define BASEDEF_H

#  ifdef WIN32
#  define DLL_EXPORT __declspec(dllexport)
#  else
#  define DLL_EXPORT
#  endif

typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int    uint32;
typedef char   int8;
typedef short  int16;
typedef int    int32;

#define U8  unsigned char
#define U16 unsigned short
#define U32 unsigned int

#define S8  char
#define S16 short
#define S32 int

#define NO_ERR  0
#define ERR_1   1

#define RELEASE_PNT(POINTER)    if(NULL != POINTER){delete POINTER;POINTER=NULL;}

#endif // BASEDEF_H
