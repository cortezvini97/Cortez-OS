section .text
global inportb

inportb:
    push ebp
    mov ebp, esp
    mov dx, word [ebp+8]
    in al, dx
    pop ebp
    ret

section .data