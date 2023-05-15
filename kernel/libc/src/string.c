#include "../include/string.h"

void* memcpy( void* destination, const void* source,size_t size)
{
    return destination;
}

size_t strlen(const char * string)
{
    int len = 0;
    while (string[len] != '\0') 
    {
        len++;
    }
    return len;
}