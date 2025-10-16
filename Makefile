DEFAULTARCH=i386
ARCH?=$(DEFAULTARCH)

ARCHDIR=arch/$(ARCH)
INCLUDEDIR=include

CFLAGS=-ffreestanding -I$(INCLUDEDIR)
CC=./.crosscompile/bin/$(ARCH)-elf-gcc
LD=./.crosscompile/bin/$(ARCH)-elf-ld

include $(ARCHDIR)/make.config

OBJS=\
	$(ARCHOBJS) \
	kernel/kernel.o \

image.bin: $(ARCHDIR)/boot/bootsect.bin kernel.bin
	cat $^ > $@
	echo $(CFLAGS) | tr ' ' '\n' > compile_flags.txt

kernel.bin: ${OBJS}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

run: image.bin
	qemu-system-i386 $<

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm *.bin
	rm kernel/*.o arch/i386/boot/*.o arch/i386/boot/*.bin arch/i386/*.o arch/i386/vga/*.o
