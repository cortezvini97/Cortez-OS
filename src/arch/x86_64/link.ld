OUTPUT_FORMAT(elf64-x86-64)
ENTRY(start)
SECTIONS
{
    . = 1M;
    .boot : 
    { 
        KEEP(*(.multiboot_header))
    }
    .text : { *(.text) }
    .data : { *(.data) }
    .bss  : { *(.bss)  }
}