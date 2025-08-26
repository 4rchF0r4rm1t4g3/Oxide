as = i686-elf-as
nasm = nasm
ld = i686-elf-ld
cc = i686-elf-gcc

compile:
	$(as) -o build/boot.o src/boot.s
	$(nasm) -f elf32 src/idt.s -o build/idt_asm.o
	$(cc) -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(cc) -c src/out.c -o build/out.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(cc) -c src/idt.c -o build/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(cc) -T linker.ld -o build/kernel.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o build/out.o build/idt.o build/idt_asm.o -lgcc