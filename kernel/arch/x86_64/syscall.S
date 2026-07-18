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
    push %rcx
    push %r11

    # Call dispatcher
    # Map registers from user syscall to kernel syscall_dispatch parameters:
    # user syscall: rax=num, rdi=arg1, rsi=arg2, r10=arg3, r8=arg4, r9=arg5
    # kernel C++:   rdi=num, rsi=arg1, rdx=arg2, rcx=arg3, r8=arg4, r9=arg5
    mov %r10, %rcx   # rcx gets arg3 (from r10)
    mov %rsi, %rdx   # rdx gets arg2 (from rsi)
    mov %rdi, %rsi   # rsi gets arg1 (from rdi)
    mov %rax, %rdi   # rdi gets num  (from rax)
    call syscall_dispatch

    # Restore context
    pop %r11
    pop %rcx

    mov %gs:0x0, %rsp
    swapgs
    sysretq
