;修改段寄存器
mov ax, 0x07C0
mov ds ,ax

;清屏
mov ax, 0x0600
mov bx, 0x0700
mov cx, 0
mov dx, 184fh
int 0x10


;搬家
mov ax, 0x9000
mov es, ax

;mov ax, 0x4F02
;mov bx, 0x4180
;int 0x10

;cx是loop得循环次数
mov cx, 256
sub si, si
sub di, di
;movsb(move bytes) movsw(move words)
;原始数据段由 DS:SI 指定
;目的数据段由 ES:DI 指定
;传送方向由标志寄存器FLAGS决定（增？减）
cld
rep movsw

;搬完了

;去新家
jmp 0x9000:go
go:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    ;初始化栈顶地址（SS:SP是栈的地址）
    mov sp, 0xFF00
    jmp LoadSetup

;加载loader程序 setup.asm
LoadSetup:
    ; print message
    push ds 
    mov ax, 0b800h
    mov ds, ax
    mov byte [0x00],'L'
    mov byte [0x02],'o'
    mov byte [0x04],'a'
    mov byte [0x06],'d'
    mov byte [0x08],'i'
    mov byte [0x0a],'n'
    mov byte [0x0c],'g'
    mov byte [0x0e],' '
    mov byte [0x10],'L'
    mov byte [0x12],'o'
    mov byte [0x14],'a'
    mov byte [0x16],'d'
    mov byte [0x18],'e'
    mov byte [0x1a],'r'
    pop ds 

    ;这里我们打算把第二个扇区开始往后4个扇区
    ;读到0x90200去，可以发现上文ds的值是0x9000
    mov ah, 2          ;功能号（2表示读取）
    mov al, 4          ;这个参数表示要读取的扇区的数量
    mov ch, 0          ;这个参数表示要读取的磁道号
    mov cl, 2          ;这个参数表示要读取的起始扇区的扇区号
    mov dh, 0          ;磁头号
    mov dl, 0          ;驱动器号
    mov bx, 0x0200     ;es:bx指接受从扇区读入的数据的内存区

    int 0x13           ;read disk!!!!!!!!!!

;这里读取失败应该重新读取，以后再补全

    jmp LoadKernel       

;加载完成 加载真正的内核文件
LoadKernel:
    ;load 240 sector
    push ds 
    mov ax, 0b800h
    mov ds, ax
    mov byte [0x50],'L'
    mov byte [0x52],'o'
    mov byte [0x54],'a'
    mov byte [0x56],'d'
    mov byte [0x58],'i'
    mov byte [0x5a],'n'
    mov byte [0x5c],'g'
    mov byte [0x5e],' '
    mov byte [0x60],'K'
    mov byte [0x62],'e'
    mov byte [0x64],'r'
    mov byte [0x66],'n'
    mov byte [0x68],'e'
    mov byte [0x6a],'l'
    pop ds 

    ;这里我们打算把第6个扇区开始往后240个扇区
    ;读到0x00000去，可以发现上文ds的值是0x9000,先修改
    push es
    mov ax, 0x0000
    mov es, ax

    mov ah, 2          ;功能号（2表示读取）
    mov al, 20        ;这个参数表示要读取的扇区的数量
    mov ch, 0          ;这个参数表示要读取的磁道号
    mov cl, 6          ;这个参数表示要读取的起始扇区的扇区号
    mov dh, 0          ;磁头号
    mov dl, 0          ;驱动器号
    mov bx, 0x1000     ;es:bx指接受从扇区读入的数据的内存区

    int 0x13           ;read disk!!!!!!!!!!

    pop es

    jmp 0x9020:0x0000      ;跳到第二扇区（加载到内存里面所占的空间）加载setup程序
times 510-($-$$) db 0
db 0x55,0xaa


