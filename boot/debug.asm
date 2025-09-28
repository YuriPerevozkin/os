;-----------------------------
; Print a string on the screen
; You can pass either a quoted string or a data label that points to string
%macro Print 1
    %ifid %1
        mov si, %1
    %else
        jmp %%skip
        %%string: db %1, 0
        %%skip
        mov si, %%string
    %endif
    call print
%endmacro

;---------------------------------------------------------
; Print a character on the screen with bios 10h interrupt:
; https://en.wikipedia.org/wiki/INT_10H
%macro Printch 1
    mov ah, 0x0e
    mov al, %1
    int 0x10
%endmacro

;------------------------------------
; Print a string and start a new line
%macro Println 1
    Print %1
    Printch 13
    Printch 10
%endmacro

;----------------------------------------------------
; Print a hexidecimal represintation of a given value
%macro Printhex 1
    mov si, %1
    call printhex
%endmacro

;---------------------------
; `Print` macro implementation
; arguments - si
;   iterate a string and print each char. Stop on null byte (0x00)
print:
    push ax

    .loop:
        lodsb
        or al, al
        jz .done
        mov ah, 0x0e
        int 0x10
        jmp .loop
    .done:
        pop ax
        ret

;------------------------------
; `Printhex` macro implementation
; arguments - si
;   iterate over given value and increment each char by 30h (30h-39h are ascii value for "0"-"9")
;   add 7 if char is not a number (look for ascii values for alphabetic characters)
;   terminate after four iterations and print the result
HEX_OUT db "0x0000", 0
printhex:
    push cx
    push ax
    push bx

    mov cx, 0

    .loop:
        cmp cx, 4
        je .done

        mov ax, si
        and ax, 0x000f
        add al, 0x30
        cmp al, 0x39
        jle .hexout
        add al, 7

    .hexout:
        mov bx, HEX_OUT + 5
        sub bx, cx
        mov [bx], al
        ror si, 4

        add cx, 1
        jmp .loop

    .done:
        Println HEX_OUT

        pop bx
        pop ax
        pop cx
        ret
