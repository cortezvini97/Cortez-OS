section .text
    global _start_kernel
    extern main_kernel
    extern system_inportb
    extern system_outportb
    extern system_shutdown
    extern system_reboot

_start_kernel:
    call main_kernel
    hlt

system_inportb:
    push ebp
    mov ebp, esp
    mov dx, word [ebp+8]
    in al, dx
    pop ebp
    ret

system_outportb:
    mov dx, word [esp + 4]   
    mov al, byte [esp + 8] 
    out dx, al      
    ret                   

system_shutdown:
    mov dx, 0x604      ; Porta usada pelo ACPI no QEMU
    mov ax, 0x2000     ; Comando para desligar
    out dx, ax
    hlt    



system_reboot:
    mov dx, 0x64
    mov al, 0xFE
    out dx, al
    hlt