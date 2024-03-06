
ASMFLAGS = -f elf32
CFLAGS = -m32 -c -I
LinkFLAGS = -m elf_i386 -T
CTMP = $(wildcard src/C_files/*.c)
CFILE = $(subst src/C_files/, ,$(CTMP))
CSRC = $(CFILE:.c=)
ATMP = $(wildcard src/assembly_files/*.asm)
ASMFILE = $(subst src/assembly_files/, ,$(ATMP))
ASRC = $(ASMFILE:.asm=)

all: compileAsm compileC linkerFiles buildIso

compileAsm:
	mkdir -p build
	for file in $(ASRC) ; do \
		nasm $(ASMFLAGS) src/assembly_files/$$file.asm -o build/$$file.o ; \
	done

compileC:
	for file in $(CSRC) ; do \
		gcc $(CFLAGS) src/C_files/includes src/C_files/$$file.c -o build/$$file.o -ffreestanding; \
	done

linkerFiles:
	mkdir -p dist
	ld ${LinkFLAGS} link.ld -o cortezos/boot/kernel.bin build/main.o build/kernel.o build/system.o build/string.o build/screen.o build/keyboard.o

buildIso:
	grub-mkrescue -o dist/cortezos.iso cortezos/