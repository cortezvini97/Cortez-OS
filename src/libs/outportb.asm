section .text
global outportb

outportb:
    ; Argumentos:
    ;   _port: DX
    ;   _data: AL

    mov dx, word [esp + 4]     ; Carrega o valor de _port (2 bytes) no registrador DX
    mov al, byte [esp + 8]     ; Carrega o valor de _data (1 byte) no registrador AL

    out dx, al                 ; Escreve o byte em AL na porta especificada em DX

    ret                         ; Retorna