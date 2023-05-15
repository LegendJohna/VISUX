extern __main
[bits 32]
;进入保护模式BIOS没用了，把0x1000以下的地址利用起来，先清零吧
mov eax, 0
mov ecx, 0x1000
clear:
    mov [eax], byte 0
    inc eax
    loop clear

;重新设置IDT，GDT
call SetupGDT 
call SetupIDT
;重新初始化栈寄存器决定栈位置

;开启分页模式，把物理地址高低1GB映射到虚拟地址高1GB去

;正式进入main函数
push __main
jmp __main
jmp $

GDT48:
     dw 24 - 1 ;三个段描述符
     dd 0x0000 ;起始地址0x00000000

GDT: 
    dw 0,0,0,0 ; 空描述符

    ;代码段,都是4GB的大小
    dw 0x07FF  ;8mb - limit = 2047
    dw 0x0000  ;base address = 0
    dw 0x9A00  ;code read/exec
    dw 0x00C0  ;granularity = 4096, 386

    ;数据段
    dw 0x07FF  ; 8Mb - limit = 2047
    dw 0x0000  ; base address =0
    dw 0x9200  ; data read/write
    dw 0x00C0  ;granularity = 4096, 386
SetupGDT:
    ;movsb(move bytes) movsw(move words)
    ;原始数据段由 DS:SI 指定
    ;目的数据段由 ES:DI 指定
    ;传送方向由标志寄存器FLAGS决定（增？减）
    mov ecx, 24
    sub esi, esi
    sub edi, edi
    mov esi, GDT
    cld
    rep movsb
    lgdt [GDT48]
    ret
IDT48:
    dw 256*8 - 1 ;256个中断描述符
    dd 0x0000024 ;起始地址仅仅挨着GDT后面
SetupIDT:
    ;目前没有中断，后面会在c语言部分添加
    lidt [IDT48]
    ret






