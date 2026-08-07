.section .text
.global context_switch

# void context_switch(u64* old_stack_ptr, u64 new_stack_ptr)
# rdi = old_stack_ptr, rsi = new_stack_ptr
context_switch:
    push %rbp
    push %rbx
    push %r12
    push %r13
    push %r14
    push %r15
    
    mov %rsp, (%rdi)
    mov %rsi, %rsp
    
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %rbx
    pop %rbp
    
    ret

.global enter_user_mode
# void enter_user_mode(u64 entry, u64 stack)
enter_user_mode:
    # Subtract 8 from stack pointer to ensure 16-byte alignment of stack frames in user mode
    sub $8, %rsi
    mov %rsi, %rsp

    # Push SS (User Data - index 3, RPL 3 = 0x1B)
    push $0x1B
    # Push RSP
    push %rsi
    # Push RFLAGS (Interrupts enabled)
    pushfq
    pop %rax
    or $0x200, %rax
    push %rax
    # Push CS (User Code - index 4, RPL 3 = 0x23)
    push $0x23
    # Push RIP
    push %rdi

    # Zero out registers to avoid info leaks
    xor %rax, %rax
    xor %rbx, %rbx
    xor %rcx, %rcx
    xor %rdx, %rdx
    xor %rsi, %rsi
    xor %rdi, %rdi
    xor %rbp, %rbp
    xor %r8, %r8
    xor %r9, %r9
    xor %r10, %r10
    xor %r11, %r11
    xor %r12, %r12
    xor %r13, %r13
    xor %r14, %r14
    xor %r15, %r15

    iretq

.global child_fork_return
child_fork_return:
    # rdi points to SyscallRegs structure:
    # 0: rbx, 8: rbp, 16: rdi, 24: rsi, 32: rdx, 40: r10, 48: r8, 56: r9, 64: r12, 72: r13, 80: r14, 88: r15, 96: rflags, 104: rip, 112: rsp

    # Restore callee-saved and caller-saved registers
    mov 0(%rdi), %rbx
    mov 8(%rdi), %rbp
    mov 24(%rdi), %rsi
    mov 32(%rdi), %rdx
    mov 40(%rdi), %r10
    mov 48(%rdi), %r8
    mov 56(%rdi), %r9
    mov 64(%rdi), %r12
    mov 72(%rdi), %r13
    mov 80(%rdi), %r14
    mov 88(%rdi), %r15

    # Load rflags into %r11
    mov 96(%rdi), %r11
    # Load rip into %rcx
    mov 104(%rdi), %rcx
    # Load rsp into %gs:0x0 (user stack pointer)
    mov 112(%rdi), %rax
    mov %rax, %gs:0x0

    # Set RAX to 0 (fork return value for child)
    xor %rax, %rax

    # Finally, restore rdi
    mov 16(%rdi), %rdi

    # SwapGS, restore stack, and return to user space
    swapgs
    mov %gs:0x0, %rsp
    sysretq
