SOURCES = $(wildcard kernel/*.c kernel/drivers/*.c)
HEADERS = $(wildcard kernel/*.h)
OBJ = ${SOURCES:.c=.o}

GCC = ./.crosscompile/bin/i386-elf-gcc
LD = ./.crosscompile/bin/i386-elf-ld

image.bin: boot/bootsect.bin kernel.bin
	cat $^ > $@

kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.o: kernel/kernel.c
	${GCC} -ffreestanding -c $< -o $@

run: image.bin
	qemu-system-i386 $<

%.o: %.c ${HEADERS}
	${GCC} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm *.bin
	rm kernel/*.o boot/*.o boot/*.bin kernel/drivers/*.o
