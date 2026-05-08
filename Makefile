CFLAGS = -m32 -fno-stack-protector -fno-builtin

all: clean kernel boot image

clean:
	rm -rf *.o

kernel:
	gcc $(CFLAGS) -c src/kernel.c -o kernel.o
	gcc $(CFLAGS) -c src/vga.c -o vga.o
	gcc $(CFLAGS) -c src/gdt/gdt.c -o gdt.o
	gcc $(CFLAGS) -c src/util.c -o util.o
	gcc $(CFLAGS) -c src/interrupts/idt.c -o idt.o
	gcc $(CFLAGS) -c src/timer.c -o timer.o
	gcc $(CFLAGS) -c src/keyboard.c -o keyboard.o
	gcc $(CFLAGS) -c src/stdlib/stdio.c -o stdio.o
	gcc $(CFLAGS) -c src/commands/help.c -o help.o
	gcc $(CFLAGS) -c src/commands/uptime.c -o uptime.o
	gcc $(CFLAGS) -c src/commands/clear.c -o clear.o

boot: 
	nasm -f elf32 src/boot.s -o boot.o
	nasm -f elf32 src/gdt/gdt.s -o gdts.o
	nasm -f elf32 src/interrupts/idt.s -o idts.o


image:
	ld -m elf_i386 -T linker.ld -o kernel boot.o kernel.o vga.o gdt.o gdts.o util.o idt.o idts.o timer.o keyboard.o stdio.o help.o uptime.o clear.o
	mv kernel RADOS/boot/kernel
	grub-mkrescue -o kernel.iso RADOS/
	rm *.o
