;---------------------------------------------------------
; enable a20 line (https://en.wikipedia.org/wiki/A20_line)
;   first step - try bios interrupt. If not supported jump to second step.
;   second step - try fast a20. If not supported jump to third step.
;   third step - try to access 0xee. If failed give up.
;
; cf - return value
;   0 - success
;   1 - failure
enablea20:
    push ax

    call a20check
    test ax, ax
    jnz .done

    ; bios a20

    mov ax, 0x2401
    int 0x15
    jnc .done
    
    ; fast a20

    in al, 0x92
    test al, 2
    jnz .done

    or al, 2
    and al, 0xfe
    out 0x92, al

    call a20check
    test ax, ax
    jnz .done

    ; 0xee access

    in al, 0xee

    call a20check
    test ax, ax
    jnz .done

    stc

    .done:
        pop ax
        ret

;-------------------------
; check if a20 is enabled
;
; ax - return value
;   0 - a20 is disabled
;   1 - a20 is enabled
a20check:
    pushf
    push ds

    not ax
    mov ds, ax

    mov di, 0x0500
    mov si, 0x0510

    mov al, byte [es:di]
    push ax

    mov al, byte [ds:si]
    push ax

    mov byte [es:di], 0x00
    mov byte [ds:si], 0xFF

    cmp byte [es:di], 0xFF ; if equal then a20 is disabled

    pop ax
    mov byte [ds:si], al

    pop ax
    mov byte [es:di], al

    mov ax, 0
    je .done

    mov ax, 1

    .done:
        pop ds
        popf

        ret
