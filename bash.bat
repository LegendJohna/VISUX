@echo off
chcp 65001
nasm boot/bootsector.asm -o bin/bootsector.bin
nasm boot/setup.asm -o bin/setup.bin

nasm -f win32 boot/head.asm -o bin/head.obj
gcc -c -x c -fno-builtin -ffreestanding -fno-ident -nostdinc -nostdlib -m32 kernel/main.c -o bin/main.obj

ld -m i386pe -N -nostdlib -e _start -Ttext 0x0 bin/head.obj bin/main.obj -o bin/kernel.obj

objcopy -O binary bin/kernel.obj bin/kernel.bin

copy /B bin\bootsector.bin + bin\setup.bin + bin\kernel.bin main.img


objdump -d bin/main.obj > log/main.txt                        
objdump -d bin/head.obj > log/head.txt
objdump -d bin/kernel.obj > log/kernel.txt
objdump -D -b binary -m i386 bin/kernel.bin > log/bin.txt
