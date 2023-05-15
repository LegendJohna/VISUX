#ifndef _SYSTEM_TIMER_H
#define _SYSTEM_TIMER_H

#include "../../../libc/include/stdarg.h"

void InitlizeTimer(uint32_t frequency);

void TimerInterruptHandler();


#endif