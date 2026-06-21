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

.global isr_gp_handler
isr_gp_handler:
    cli
    push %rax
    push %rcx
    push %rdx
    push %rsi
    push %rdi
    push %r8
    push %r9
    push %r10
    push %r11

    # Error code is at [rsp + 72]
    # RIP is at [rsp + 80]
    mov 80(%rsp), %rdi
    mov 72(%rsp), %rsi
    call k_handle_gp

    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rdi
    pop %rsi
    pop %rdx
    pop %rcx
    pop %rax
    add $8, %rsp # Error code
    iretq

.global isr_pf_handler
isr_pf_handler:
    cli
    push %rax
    push %rcx
    push %rdx
    push %rsi
    push %rdi
    push %r8
    push %r9
    push %r10
    push %r11

    # RIP is at [rsp + 80]
    # Error code is at [rsp + 72]
    mov 80(%rsp), %rdi
    mov 72(%rsp), %rsi
    mov %cr2, %rdx
    call k_handle_pf

    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rdi
    pop %rsi
    pop %rdx
    pop %rcx
    pop %rax
    add $8, %rsp # Error code
    iretq

.global isr_df_handler
isr_df_handler:
    cli
    push %rax
    push %rcx
    push %rdx
    push %rsi
    push %rdi
    push %r8
    push %r9
    push %r10
    push %r11

    # Error code is at [rsp + 72]
    # RIP is at [rsp + 80]
    mov 80(%rsp), %rdi
    mov 72(%rsp), %rsi
    call k_handle_df

    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rdi
    pop %rsi
    pop %rdx
    pop %rcx
    pop %rax
    add $8, %rsp # Error code
    iretq

.section .bss
.align 16
stack_bottom:
    .skip 16384 # 16KiB stack
stack_top:
