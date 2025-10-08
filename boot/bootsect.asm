[BITS 16]
[ORG 0x7c00]

jmp start

%include "boot/a20.asm"
; for debugging
; %include "boot/debug.asm"

STACK_BASE16 equ 0x7c00
STACK_BASE32 equ 0x90000
KERNEL_OFFSET equ 0x1000
BOOT_SIGNATURE equ 0xaa55

; https://en.wikipedia.org/wiki/Global_Descriptor_Table
GDT_START:
    dq 0
GDT_CODE:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0
GDT_DATA:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
GDT_END:

GDT:
    dw GDT_END - GDT_START - 1
    dd GDT_START

CODE_SEG equ GDT_CODE - GDT_START
DATA_SEG equ GDT_DATA - GDT_START

start:
    cld     ; clear direction flag used in Print by lodsb

    cli     ; disable iterrupts - environment is unstable right now (never enabled them after lol)

    ; zero out segment registers
    
    xor ax, ax  ; ax = 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    
    ; set up the stack

    mov bp, STACK_BASE16
    mov sp, bp

    ; a20.asm

    call enablea20

    ; load kernel from disk

    mov bx, KERNEL_OFFSET
    mov ah, 0x02    ; 0x02 = read
    mov al, 3       ; number of sectors to read
    mov ch, 0       ; cylinder
    mov dh, 0       ; head number
    mov cl, 2       ; sector number
    int 0x13

    ; enter 32 bit protected mode

    lgdt [GDT]

    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:pm_start

[BITS 32]
pm_start:
    ; we're in protected mode now, set up segment registers
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; and stack
    mov ebp, STACK_BASE32
    mov esp, ebp

    call KERNEL_OFFSET ; give control to the kernel!

    ; do nothing
halt:
    hlt
    jmp halt

times 510-($-$$) db 0   ; fill the rest with zeros
dw BOOT_SIGNATURE       ; necessary for some bioses
