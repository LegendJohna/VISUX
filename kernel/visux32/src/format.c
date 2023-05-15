#include "../include/format.h"

const int DisplayAddress = 0xb8000;

void Write(int address, char message)
{
    (*(unsigned char*)(address)) = message;
}
int TextPtr = 0;
void clear()
{
    for(int i = 0;i < 80*25;i++)
    {
        Write(DisplayAddress + 2 * i, 32);
    }
    TextPtr = 0;
}
void print(const char* message)
{
    for(int i = 0; message[i] != '\0'; i++)
    {
        if(message[i] == '\n')
        {
            TextPtr = 80 * (TextPtr / 80 + 1);
        } 
        else 
        {
            Write(DisplayAddress  + 2 * TextPtr, message[i]);
            TextPtr++;
        }
    }
}
    

void printNumber(int x)
{
    char result[10];
    char str[10];
    int ptr = 0;
    str[ptr] = ((x % 10) + 48);
    while (x / 10 != 0)
    {
        x = x / 10;
        ptr++;
        str[ptr] = (char)((x % 10) + 48);  
    }
    result[ptr+1] = '\0';
    int temp = ptr;
    while (ptr >= 0)
    {
        result[temp-ptr] = str[ptr];
        ptr--;
    }
    print(result);
}
void printHex(int x)
{
    char result[10];
    char str[10];
    int ptr = 0;
    str[ptr] = (x % 16 < 10?(x % 16 + 48):(x % 16 + 55));
    while (x / 16 != 0)
    {
        x = x / 16;
        ptr++;
        str[ptr] = (x % 16 < 10?(x % 16 + 48):(x % 16 + 55));
         
    }
    result[ptr+1] = '\0';
    int temp = ptr;
    while (ptr >= 0)
    {
        result[temp-ptr] = str[ptr];
        ptr--;
    }
    print(result);
}



int format(const char* message, ...)
{
    char buffer[100];
    int stackAddress = (int)(&message) + sizeof(void*);
    int bufferPtr = 0;
    for(int i = 0; message[i] != '\0'; i++)
    {
        if(message[i] != '{')
        {
            buffer[bufferPtr] = message[i];
            bufferPtr++;
        }
        else
        {
            if(message[i+1] == 'i'&& message[i+2] == 'n'&& message[i+3] == 't' &&message[i+4] == '}')
            {
                int value = *(int*)stackAddress;
                char str[10];
                int ptr = 0;
                str[ptr] = (char)((value % 10) + 48);
                while (value / 10 != 0)
                {
                    value = value / 10;
                    ptr++;
                    str[ptr] = (char)((value % 10) + 48);
                }
                bufferPtr += ptr;
                while (ptr >= 0)
                {
                    buffer[bufferPtr-ptr] = str[ptr];
                    ptr--;
                }
                i += 4;
                stackAddress += sizeof(void*);
                bufferPtr++;
            }
            else if(message[i+1] == 's'&& message[i+2] == 't'&& message[i+3] == 'r' &&message[i+4] == 'i'&&
            message[i+5] == 'n'&& message[i+6] == 'g'&& message[i+7] == '}')
            {
                char* str = *(char**)stackAddress;
                for(int j = 0;str[j] != '\0';j++)
                {
                    buffer[bufferPtr] = str[j];
                    bufferPtr++;
                }
                i += 7;
                stackAddress += sizeof(void*);
            }
        }
    }
    buffer[bufferPtr] = '\0';
    print(buffer);
    return bufferPtr;
}