.section .text
.global syscall_entry

# SYSCALL entry point
# rcx = return address
# r11 = rflags
# rax = syscall number
# rdi, rsi, rdx, r10, r8, r9 = args
syscall_entry:
    swapgs
    mov %rsp, %gs:0x0   # Save user stack in the per-CPU syscall area
    mov %gs:0x8, %rsp   # Load kernel stack

    # Save user context
    push %gs:0x0        # Save User RSP on the private kernel stack
    push %rcx           # User RIP
    push %r11           # User RFLAGS
    push %r15
    push %r14
    push %r13
    push %r12
    push %r9
    push %r8
    push %r10
    push %rdx
    push %rsi
    push %rdi
    push %rbp
    push %rbx

    # Call dispatcher
    # Map registers from user syscall to kernel syscall_dispatch parameters:
    # user syscall: rax=num, rdi=arg1, rsi=arg2, r10=arg3, r8=arg4, r9=arg5
    # kernel C++:   rdi=num, rsi=arg1, rdx=arg2, rcx=arg3, r8=arg4, r9=arg5
    sub $8, %rsp     # Align stack to 16-byte boundary before function call
    mov %r10, %rcx   # rcx gets arg3 (from r10)
    mov %rsi, %rdx   # rdx gets arg2 (from rsi)
    mov %rdi, %rsi   # rsi gets arg1 (from rdi)
    mov %rax, %rdi   # rdi gets num  (from rax)
    call syscall_dispatch
    add $8, %rsp     # Restore stack alignment

    # Restore context
    pop %rbx
    pop %rbp
    pop %rdi
    pop %rsi
    pop %rdx
    pop %r10
    pop %r8
    pop %r9
    pop %r12
    pop %r13
    pop %r14
    pop %r15
    pop %r11
    pop %rcx
    pop %gs:0x0         # Restore User RSP from the private kernel stack

    mov %gs:0x0, %rsp
    swapgs
    sysretq
