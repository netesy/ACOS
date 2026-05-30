.section .text
.global _start

_start:
    cli
    # Setup stack
    mov $stack_top, %rsp

    # Call kernelMain
    # BootInfo* is passed in %rdi by the bootloader
    call kernelMain

_halt:
    hlt
    jmp _halt

.section .bss
.align 16
stack_bottom:
    .skip 16384 # 16KiB stack
stack_top:

.section .note.GNU-stack,"",@progbits
