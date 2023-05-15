#ifndef _STDARG_H
#define _STDARG_H

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;
typedef unsigned long long size_t;

typedef unsigned char* va_list;
#define va_start(ap,v) ap = (va_list)&v
#define va_arg(ap,t) *((t*)(ap += 4))
#define va_end(ap) ap = NULL

#endif 