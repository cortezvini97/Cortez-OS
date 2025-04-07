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
    ; RDI = port (uint16_t)
    ; Return value will be in RAX
    mov dx, di      ; Move lower 16 bits of RDI to DX
    in al, dx       ; Read from port
    movzx rax, al   ; Zero-extend result to 64 bits
    ret

system_outportb:
    ; RDI = port (uint16_t), RSI = value (uint8_t)
    mov dx, di      ; Port -> DX
    mov al, sil     ; Value -> AL (lowest 8 bits of RSI)
    out dx, al      ; Write value to port
    ret

system_shutdown:
    mov dx, 0x604   ; ACPI port used by QEMU
    mov ax, 0x2000  ; Shutdown command
    out dx, ax      ; Send lower part of EAX (AX) to port
    hlt             ; Halt CPU if shutdown fails

system_reboot:
    mov dx, 0x64    ; Keyboard controller command port
    mov al, 0xFE    ; Magic command for reboot
    out dx, al      ; Trigger reboot
    hlt             ; Halt CPU if reboot fails