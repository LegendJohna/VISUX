#include "../include/interrupt.h"
#include "../include/timer.h"
#include "../include/keyboard.h"
typedef struct InterruptDescriptor
{
    uint16_t offsetLow;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t offsetHigh;
} InterruptDescriptor;

static InterruptDescriptor* IDT = (InterruptDescriptor*)24;
void Initlize8259A()
{
    //设置8259A中断控制器
    OutByte(0x20, 0x11); //ICW1：边沿触发/级联方式
    OutByte(0x21, 0x20); //ICW2:起始中断向量
    OutByte(0x21, 0x04); //ICW3:主片级联到IR2                    
    OutByte(0x21, 0x01); //ICW4:非总线缓冲，全嵌套，正常EOI
    OutByte(0xA0, 0x11); //ICW1：边沿触发/级联方式
    OutByte(0xA1, 0x70); //ICW2:起始中断向量
    OutByte(0xA1, 0x04); //ICW3:从片级联到IR2
    OutByte(0xA1, 0x01); //ICW4:非总线缓冲，全嵌套，正常EOI      
}
void InitlizeHardware()
{
    Initlize8259A();
    InitlizeTimer(100);
    InitlizeKeyboard();
}

void InitlizeInterrupts()
{
    for(int i = 0; i < 256; i++)
    {
        IDT[i].offsetLow = 0;
        IDT[i].selector = 0;
        IDT[i].zero = 0;
        IDT[i].flags = 0;
        IDT[i].offsetHigh = 0;
    }
    InitlizeHardware();
    SetupInterrupt(TIMER_INTERRUPT,TimerInterruptHandler ,0 );
    SetupInterrupt(KEYBOARD_INTERRUPT,KeyboardInterruptHandler,0 );
}

void SetupInterrupt(InterruptNumber number, void (*handler)(), uint8_t flags)
{
    IDT[number].offsetLow = (uint32_t)handler & 0x0000FFFF;
    IDT[number].selector = 8;
    IDT[number].zero = 0;
    IDT[number].flags = flags;
    IDT[number].offsetHigh = ((uint32_t)handler & 0xFFFF0000) >> 16;
}

void OutByte(uint16_t port, uint8_t data)
{
    asm volatile ("outb %b0, %w1" : : "a" (data), "Nd" (port));
}

void OutWord(uint16_t port, uint16_t data)
{
    asm volatile ("outw %w0, %w1" : : "a" (data), "Nd" (port));
}

void OutDWord(uint16_t port, uint32_t data)
{
    asm volatile ("outl %0, %w1" : : "a" (data), "Nd" (port));
}

void OutByteFromBuffer(uint16_t port, uint8_t *data, uint32_t size)
{
    for(uint32_t i = 0; i < size; i++)
    {
        OutByte(port, data[i]);
    }
}

uint8_t InByte(uint16_t port)
{
    uint8_t data;
    asm volatile ("inb %w1, %b0" : "=a" (data) : "Nd" (port));
    return data;
}

uint16_t InWord(uint16_t port)
{
    uint16_t data;
    asm volatile ("inw %w1, %w0" : "=a" (data) : "Nd" (port));
    return data;
}

uint32_t InDWord(uint16_t port)
{
    uint32_t data;
    asm volatile ("inl %w1, %0" : "=a" (data) : "Nd" (port));
    return data;
}

void InByteToBuffer(uint16_t port, uint8_t *data, uint32_t size)
{
    for(uint32_t i = 0; i < size; i++)
    {
        data[i] = InByte(port);
    }
}

