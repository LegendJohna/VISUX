SRC := $(shell dir /s /b kernel\*.c)
OBJ := $(patsubst %.c, build/obj/%.obj, $(notdir $(SRC)))

$(info $(SRC))
$(info $(OBJ))

# 设置默认目标
all: VISUX.img

# 生成二进制文件
build/bin/bootsector.bin: boot/bootsector.asm
	nasm $< -o $@

build/bin/setup.bin: boot/setup.asm
	nasm $< -o $@

build/obj/head.obj: boot/head.asm
	nasm -f win32 $< -o $@

$(OBJ)/%.obj: $(SRC)/%.c
	gcc -c -x c -fno-builtin -ffreestanding -fno-ident -nostdinc -nostdlib -m32 $< -o $@


build/obj/kernel.obj: build/obj/head.obj $(OBJ)
	ld -m i386pe -N -nostdlib --no-dynamic-linker -T linker.ld --image-base=0  $^ -o $@

build/bin/kernel.bin: build/obj/kernel.obj
	objcopy -O binary $< $@

# 生成内核镜像
VISUX.img: build/bin/bootsector.bin build/bin/setup.bin build/bin/kernel.bin
	copy /B build\bin\bootsector.bin + build\bin\setup.bin + build\bin\kernel.bin VISUX.img
	
# 生成反汇编日志
build/log/%.txt: $(OBJ_DIR)/%.obj
	objdump -D $< > $@

clean:
	(info )
	del /q build

.PHONY: all clean
