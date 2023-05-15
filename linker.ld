OUTPUT_FORMAT("pei-i386")
OUTPUT_ARCH(i386)
ENTRY(__main)
SECTIONS
{
    . = 0x1000;

    _start = .;

    .text :
    {
        *(.text)
    }

    .data :
    {
        *(.data);
    }

    .rodata :
    {
        *(.rodata)
    }

    .bss :
    {
        *(.bss)
    }

    _end = .;
}