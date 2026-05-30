.section .text
.global syscall_entry

# SYSCALL entry point
# rcx = return address
# r11 = rflags
# rax = syscall number
# rdi, rsi, rdx, r10, r8, r9 = args
syscall_entry:
    swapgs
    mov %rsp, %gs:0x0   # Save user stack (placeholder for GS segment use)
    mov %gs:0x8, %rsp   # Load kernel stack

    # Save user context
    push %rcx
    push %r11

    # Call dispatcher
    # (Simplified: using r10 as 4th arg for C calling convention)
    mov %r10, %rcx
    call syscall_dispatch

    # Restore context
    pop %r11
    pop %rcx

    mov %gs:0x0, %rsp
    swapgs
    sysretq
