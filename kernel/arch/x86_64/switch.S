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
    mov %rsi, %rsp

    # Push SS (User Data)
    push $0x23
    # Push RSP
    push %rsi
    # Push RFLAGS (Interrupts enabled)
    pushfq
    pop %rax
    or $0x200, %rax
    push %rax
    # Push CS (User Code)
    push $0x1B
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
