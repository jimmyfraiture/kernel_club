CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
LLVMPATH = /bin
CLANGFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72+nosimd

all: clean kernel8.img

boot.o: boot.S
	$(LLVMPATH)/clang-15 --target=aarch64-elf $(CLANGFLAGS) -c boot.S -o boot.o

%.o: %.c
	$(LLVMPATH)/clang-15 --target=aarch64-elf $(CLANGFLAGS) -c $< -o $@

kernel8.img: boot.o $(OFILES)
	$(LLVMPATH)/ld.lld-15 -m aarch64elf -nostdlib boot.o $(OFILES) -T link.ld -o kernel8.elf
	$(LLVMPATH)/llvm-objcopy-15 -O binary kernel8.elf kernel8.img

clean:
	/bin/rm kernel8.elf *.o *.img > /dev/null 2> /dev/null || true
