CFLAGS = -m32 -fno-stack-protector -fno-builtin

all: clean kernel boot image

clean:
	rm -rf *.o

kernel:
	gcc $(CFLAGS) -c src/kernel.c          -o kernel.o
	gcc $(CFLAGS) -c src/vga.c             -o vga.o
	gcc $(CFLAGS) -c src/gdt/gdt.c         -o gdt.o
	gcc $(CFLAGS) -c src/util.c            -o util.o
	gcc $(CFLAGS) -c src/interrupts/idt.c  -o idt.o
	gcc $(CFLAGS) -c src/timer.c           -o timer.o
	gcc $(CFLAGS) -c src/keyboard.c        -o keyboard.o
	gcc $(CFLAGS) -c src/stdlib/stdio.c    -o stdio.o
	gcc $(CFLAGS) -c src/memory.c          -o memory.o
	gcc $(CFLAGS) -c src/kmalloc.c         -o kmalloc.o
	gcc $(CFLAGS) -c src/process.c         -o process.o
	gcc $(CFLAGS) -c src/scheduler.c       -o scheduler.o
	gcc $(CFLAGS) -c src/shell.c           -o shell.o
	gcc $(CFLAGS) -c src/shutdown.c        -o shutdown.o
	gcc $(CFLAGS) -c src/apps/calculator.c -o calculator.o
	gcc $(CFLAGS) -c src/apps/stopwatch.c  -o stopwatch.o
	gcc $(CFLAGS) -c src/apps/zentype.c    -o zentype.o

boot:
	nasm -f elf32 src/boot.s           -o boot.o
	nasm -f elf32 src/gdt/gdt.s        -o gdts.o
	nasm -f elf32 src/interrupts/idt.s -o idts.o
	nasm -f elf32 src/switch.asm       -o switch.o

image:
	ld -m elf_i386 -T linker.ld -o kernel \
		boot.o kernel.o vga.o gdt.o gdts.o util.o \
		idt.o idts.o timer.o keyboard.o stdio.o \
		memory.o kmalloc.o process.o scheduler.o \
		shell.o shutdown.o switch.o \
		calculator.o stopwatch.o zentype.o
	mv kernel RADOS/boot/kernel
	grub-mkrescue -o kernel.iso RADOS/
	rm *.o
