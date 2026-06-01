.section .text
.global context_switch

# void context_switch(u64* old_stack_ptr, u64 new_stack_ptr)
# rdi = old_stack_ptr, rsi = new_stack_ptr
context_switch:
    # Save callee-saved registers
    push %rbp
    push %rbx
    push %r12
    push %r13
    push %r14
    push %r15
    
    # Save FPU/SSE state if needed
    # Save callee-saved registers required by the x86_64 ABI
    # Full FPU state would require fxsave/fxrstor
    
    # Save old stack pointer
    mov %rsp, (%rdi)
    
    # Restore new stack pointer
    mov %rsi, %rsp
    
    # Restore callee-saved registers
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %rbx
    pop %rbp
    
    ret

.section .note.GNU-stack,"",@progbits
