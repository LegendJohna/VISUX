global _start
extern __main
[bits 32]
section .text
mov ax, 16
mov ds, ax
jmp _start
_start:
    jmp __main
    jmp $

