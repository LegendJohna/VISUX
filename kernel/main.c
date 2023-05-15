#define main _main

#include "visux32/include/format.h"
#include "libc/include/string.h"
#include "system/interrupt/include/interrupt.h"
int main()
{

    clear();
    InitlizeInterrupts();
    int money = strlen("Hello world");
    const char* message = "money";
    format("I have {int} {string} !\n", money, message);
    format("Hello world !\n");
    format("Hello world !\n");
    format("Hello world !\n");
    while (1)
    {
        
    }
    return 0;
}
