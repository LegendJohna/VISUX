#ifndef _VISUX_INTERRUPT_H
#define  _VISUX_INTERRUPT_H

#include "../../../libc/include/stdarg.h"

typedef enum InterruptNumber
{
    TIMER_INTERRUPT = 32,
    KEYBOARD_INTERRUPT = 33,

} InterruptNumber;

void InitlizeInterrupts();
void SetupInterrupt(InterruptNumber number, void (*handler)(), uint8_t flags);

void OutByte(uint16_t port, uint8_t data);
void OutWord(uint16_t port, uint16_t data);
void OutDWord(uint16_t port, uint32_t data);
void OutByteFromBuffer(uint16_t port, uint8_t *data, uint32_t size);


uint8_t InByte(uint16_t port);
uint16_t InWord(uint16_t port);
uint32_t InDWord(uint16_t port);
void InByteToBuffer(uint16_t port, uint8_t *data, uint32_t size);





#endif