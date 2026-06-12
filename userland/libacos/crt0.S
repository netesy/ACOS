.section .text
.global _start

_start:
    # Set up stack frame
    push %rbp
    mov %rsp, %rbp

    # Call main(0, nullptr)
    xor %rdi, %rdi
    xor %rsi, %rsi
    call main

    # Exit syscall
    # %rax contains return value from main
    mov %rax, %rdi    # status
    mov $1, %rax      # SyscallNum::Exit
    syscall

    # Should not reach here
1:  hlt
    jmp 1b
