# KernelZiole Makefile

# Tools
ASM = nasm
CC = gcc
LD = ld
GRUB = grub-mkrescue

# Flags
ASMFLAGS = -f elf32
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -Wall -Wextra -Werror -c
LDFLAGS = -m elf_i386 -T linker.ld

# Source files
BOOT_SRC = src/boot/multiboot_header.asm src/boot/boot.asm
KERNEL_SRC = src/kernel/kernel.c src/kernel/screen.c

# Output files
OBJ = $(BOOT_SRC:.asm=.o) $(KERNEL_SRC:.c=.o)
KERNEL = kernel.bin
ISO = kernel.iso

all: $(ISO)

$(ISO): $(KERNEL)
	mkdir -p iso/boot/grub
	cp $(KERNEL) iso/boot/
	echo 'menuentry "KernelZiole" {' > iso/boot/grub/grub.cfg
	echo '	multiboot /boot/$(KERNEL)' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	$(GRUB) -o $(ISO) iso

$(KERNEL): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) $(KERNEL) $(ISO)
	rm -rf iso

run:
	qemu-system-i386 -cdrom $(ISO) -serial stdio

.PHONY: all clean run