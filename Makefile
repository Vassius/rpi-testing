# Makefile for bare metal development on the Raspberry Pi
# Author: Markus Wiik

TARGET ?= arm-none-eabi

# Define directories for source and build

BUILDDIR = build/
SRCDIR = src/
INCLDIR = include/
INSTALLDIR = /Volumes/Untitled/

# Define files

LINKSCRIPT = kernel.ld

# Rules

kernel.img: kernel.elf
	$(TARGET)-objcopy $^ -O binary kernel.img

kernel.elf: $(BUILDDIR)/start.o $(BUILDDIR)/kmain.o
	$(TARGET)-ld -T $(LINKSCRIPT) $^ -o $@

$(BUILDDIR)/start.o: $(SRCDIR)/start.s
	$(TARGET)-as -o $@ $^

$(BUILDDIR)/kmain.o: $(SRCDIR)/kmain.c
	$(TARGET)-gcc -c -o $@ $^ -Wall -Werror

.PHONY: clean

clean:
	rm $(BUILDDIR)/*.o

install:
	cp kernel.img $(INSTALLDIR)
