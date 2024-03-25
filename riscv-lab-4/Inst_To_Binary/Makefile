CC=riscv64-unknown-elf-g++
CFLAGS=-march=rv32im -mabi=ilp32 -std=c99 -g3
LFLAGS=-nostartfiles

all: raw.bin extract.bin

raw.bin: start.S
	# compiles start.S into a binary file meant for a CPU
	$(CC) $(CFLAGS) $(LFLAGS) start.S -o raw.bin

extract.bin: start.S raw.bin
	# extract instructions starting at 0x200 and save it as extract.bin for our simulator
	riscv64-unknown-elf-objcopy -O binary raw.bin extract.bin

clean:
	rm -f *.bin