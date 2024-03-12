bits    32
section         .text
        align   4
        dd      0x1BADB002
        dd      0x00
        dd      - (0x1BADB002+0x00)
        
global start
extern main_kernel
start:
        cli             ;clears the interrupts 
        call main_kernel
        hlt             ; halt the cpu(pause it from executing from this address