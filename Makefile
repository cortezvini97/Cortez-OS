
ASSEMBLER = nasm
ASFLAGS = -f elf32
LINKER = ld
LDFLAGS = -m elf_i386 -T src/link.ld
COMPILER = gcc
CFLAGS = -m32 -c -I src/inc -ffreestanding


OBJS = build/kasm.o build/kc.o build/idt.o build/system.o build/inportb.o build/outportb.o build/str.o build/screen.o build/util.o build/isr.o build/keyboard.o build/shell.o
OUTPUT = cortezos/boot/kernel.bin

all:$(OBJS)
	mkdir cortezos/ -p
	mkdir cortezos/boot/ -p
	${LINKER} ${LDFLAGS} -o ${OUTPUT} $(OBJS)


build/kasm.o:src/kernel.asm
	mkdir -p build
	$(ASSEMBLER) $(ASFLAGS) -o build/kasm.o src/kernel.asm

build/inportb.o:src/libs/inportb.asm
	mkdir -p build
	$(ASSEMBLER) $(ASFLAGS) -o build/inportb.o src/libs/inportb.asm

build/outportb.o:src/libs/outportb.asm
	mkdir -p build
	$(ASSEMBLER) $(ASFLAGS) -o build/outportb.o src/libs/outportb.asm

build/kc.o:src/kernel.c
	$(COMPILER) $(CFLAGS) src/kernel.c -o build/kc.o

build/system.o:src/libs/system.c
	$(COMPILER) $(CFLAGS) src/libs/system.c -o build/system.o

build/str.o:src/str.c
	$(COMPILER) $(CFLAGS) src/str.c -o build/str.o

build/screen.o:src/screen.c
	$(COMPILER) $(CFLAGS) src/screen.c -o build/screen.o


build/idt.o:src/idt.c
	$(COMPILER) $(CFLAGS) src/idt.c -o build/idt.o


build/util.o:src/util.c
	$(COMPILER) $(CFLAGS) src/util.c -o build/util.o

build/isr.o:src/isr.c
	$(COMPILER) $(CFLAGS) src/isr.c -o build/isr.o

build/keyboard.o:src/keyboard.c
	$(COMPILER) $(CFLAGS) src/keyboard.c -o build/keyboard.o

build/shell.o:src/shell.c
	$(COMPILER) $(CFLAGS) src/shell.c -o build/shell.o
	
build:all
	rm build/ -r -f
	rm dist/ -r -f
	rm cortezos/boot/grub/ -r -f
	mkdir cortezos/boot/grub/
	echo "menuentry \"Cortez OS\" {" >> cortezos/boot/grub/grub.cfg
	echo "    multiboot /boot/kernel.bin" >> cortezos/boot/grub/grub.cfg
	echo "	boot" >> cortezos/boot/grub/grub.cfg
	echo "}" >> cortezos/boot/grub/grub.cfg
	#echo "menuentry \"Reboot\" {" >> cortezos/boot/grub/grub.cfg
	#echo "    reboot" >> cortezos/boot/grub/grub.cfg
	#echo "}" >> cortezos/boot/grub/grub.cfg
	#echo "menuentry \"Shutdown\" {" >> cortezos/boot/grub/grub.cfg
	#echo "    halt" >> cortezos/boot/grub/grub.cfg
	#echo "}" >> cortezos/boot/grub/grub.cfg
	mkdir -p dist
	grub-mkrescue -o dist/cortezos.iso cortezos/

clean:
	rm build/ -r -f
	rm dist/ -r -f
	rm cortezos/ -r -f