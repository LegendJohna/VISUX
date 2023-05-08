;获取内存信息
;Get memory size(extended memory ,KB)
mov ah, 0x88
int 0x15
mov [2], ax

;获取显卡显示信息
;Get viedo-card data
mov ah, 0x0f
int 0x10
mov [4], bx ; bh = display page
mov [6], ax ; al = viedo mode, ah = window width

;获取显示方式并且获取参数
;check for EGA/VGA and some config parameters
mov ah, 0x12
mov bl, 0x10
int 0x10
mov [8], ax
mov [10], bx
mov [12], cx


;获取第一块硬盘的信息
;Get harddisk data
mov ax, 0x0000
mov ds, ax
lds si, [4*0x41]
mov ax, 0x9000
mov es, ax
mov di, 0x0080
mov cx, 0x10
cld
rep movsb

;获取第二块硬盘信息
;Get harddisk 1 data
mov ax, 0x0000
mov ds, ax
lds si, [4*0x46]
mov ax, 0x9000
mov es, ax
mov di, 0x0090
mov cx, 0x10
cld
rep movsb

;打开高分辨率模式
mov ax,0x4F02
mov bx,0x4180
int 0x10

;把系统代码搬到最前面去0x00处
push es
push ds

mov ax, 0x1000
mov ds, ax
mov ax, 0x0000
mov es, ax
;cx是loop得循环次数
mov cx, 0x8000
sub si, si
sub di, di
;movsb(move bytes) movsw(move words)
;原始数据段由 DS:SI 指定
;目的数据段由 ES:DI 指定
;传送方向由标志寄存器FLAGS决定（增？减）
cld
rep movsw


pop ds
pop es 

;关闭BIOS中断
cli ; no interrputs allowed
 

mov ax, 0x9020
mov ds, ax

;设置段描述符寄存器和中断向量表寄存器

lgdt [ds:gdt_48] ; load gdt with whatever appropriate


;打开A20Gate!! 32位地址线路
in al, 0x92
or al, 0000_0010B
out 0x92, al

    push ds
    mov ax, 0xb800
    mov ds, ax
    mov byte [0x0150],'P'
    mov byte [0x0152],'r'
    mov byte [0x0154],'o'
    mov byte [0x0156],'t'
    mov byte [0x0158],'e'
    mov byte [0x015a],'c'
    mov byte [0x015c],'t'
    mov byte [0x015e],'e'
    mov byte [0x0160],'d'
    mov byte [0x0162],' '
    mov byte [0x0164],'M'
    mov byte [0x0166],'o'
    mov byte [0x0168],'d'
    mov byte [0x016a],'e'
    pop ds

mov ax, 0x0001 ; 打开保护模式！！ cr0 寄存器的0位置为1就行了
lmsw ax

jmp 8:0

gdt_48:
     dw 0x0800 ;gdt limit = 2048,256 GDT entries
     dd 0x90200 + gdt ;gdt base = 0x9xxxx

gdt: 
    dw 0,0,0,0 ;dummy

    dw 0x07FF  ;8mb - limit = 2047
    dw 0x0000  ;base address = 0
    dw 0x9A00  ;code read/exec
    dw 0x00C0  ;granularity = 4096, 386

    dw 0x07FF  ; 8Mb - limit = 2047
    dw 0x0000  ; base address =0
    dw 0x9200  ; data read/write
    dw 0x00C0  ;granularity = 4096, 386

times 512*4-($-$$) db 0





