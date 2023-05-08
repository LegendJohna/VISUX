#define Write(x) *(unsigned char*)(x)
#define main _main

int DisplayAddress = 0xb8000;
int head = 1;
const char str[] = "Hello world";

void print(const char* ptr)
{
    for(int i = 0; ptr[i] != '\0'; i++)
    {
        Write(DisplayAddress + 0x400 + 2*i) = ptr[i];
    }
}


int main()
{
    print(str);

    while (1)
    {
        
    }
    return 0;
}
