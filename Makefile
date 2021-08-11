all:
	@riscv64-unknown-linux-gnu-gcc -x assembler-with-cpp -march=rv64gcvxthead -mabi=lp64d -mcmodel=medlow -fno-stack-protector -g -ggdb -Wall -O3 -c entry.S -o obj/entry.o
	@riscv64-unknown-linux-gnu-gcc -march=rv64gcvxthead -mabi=lp64d -mcmodel=medlow -fno-stack-protector -g -ggdb -Wall -c main.c -o obj/main.o
	@riscv64-unknown-linux-gnu-gcc -T linker.ld -nostdlib -Wl,--cref,-Map=obj/d1-baremetal.map obj/entry.o obj/main.o -lgcc -o obj/nezha.elf
	@riscv64-unknown-linux-gnu-objcopy -v -O binary obj/nezha.elf --strip-all obj/nezha.bin
clean:
	@rm obj/*
	@echo "clean ok"
push:
	xfel ddr ddr3
	xfel write 0x40000000 obj/nezha.bin
	xfel exec 0x40000000