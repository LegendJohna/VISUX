@echo off
chcp 65001
objdump -d bin/main.obj > log/main.txt                        
objdump -d bin/head.obj > log/head.txt
objdump -d bin/kernel.obj > log/kernel.txt
objdump -D -b binary -m i386 bin/kernel.bin > log/bin.txt
