OUTPUT_FORMAT("elf64-littleriscv", "elf64-littleriscv", "elf64-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)
BASE_ADDRESS = 0x40000000;
SECTIONS
{
    . = BASE_ADDRESS;
    .text : {
        *(.text.start)
        *(.text .text.*)
    }
    . = ALIGN(4K);
    .rodata : {
        *(.rodata .rodata.*)
    }
    . = ALIGN(4K);
    .data : {
        *(.data .data.*)
    }
    . = ALIGN(4K);
    .bss : {
        *(.bss.stack)
        *(.bss .bss.*)
    }
    . = ALIGN(4K);
    /DISCARD/ : {
        *(.eh_frame)
    }
}