.section .text
.code16
.global ap_boot_start

# AP Bootstrap Code (runs in real mode at 0x8000)
ap_boot_start:
    cli
    
    # Load GDT
    lgdt ap_gdt_ptr
    
    # Enable protected mode
    mov %cr0, %eax
    or $1, %eax
    mov %eax, %cr0
    
    # Jump to protected mode
    ljmp $0x08, $ap_boot_protected
    
.code32
ap_boot_protected:
    # Load data segments
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    
    # Load temporary stack
    mov $0x9000, %esp
    
    # Enable PAE
    mov %cr4, %eax
    or $0x20, %eax
    mov %eax, %cr4
    
    # Load PML4
    mov ap_pml4_addr, %eax
    mov %eax, %cr3
    
    # Enable long mode
    mov $0xC0000080, %ecx
    rdmsr
    or $0x100, %eax
    wrmsr
    
    # Enable paging
    mov %cr0, %eax
    or $0x80000000, %eax
    mov %eax, %cr0
    
    # Jump to long mode
    ljmp $0x18, $ap_boot_long
    
.code64
ap_boot_long:
    # Load kernel stack
    mov ap_stack_ptr, %rsp
    
    # Load GS base for CPU data
    mov ap_gs_base, %rax
    mov $0xC0000101, %rcx
    mov %eax, %edx
    shr $32, %rax
    wrmsr
    
    # Call AP entry point
    mov ap_entry_point, %rax
    call *%rax
    
    # Halt if entry returns
    cli
    hlt

.section .data
.align 8
ap_gdt_ptr:
    .word ap_gdt_end - ap_gdt - 1
    .long ap_gdt

.align 8
ap_gdt:
    # Null descriptor
    .quad 0
    # Code descriptor (0x08)
    .quad 0x00209a0000000000
    # Data descriptor (0x10)
    .quad 0x0020920000000000
    # Code64 descriptor (0x18)
    .quad 0x0020980000000000
ap_gdt_end:

.align 8
ap_pml4_addr:
    .quad 0

.align 8
ap_stack_ptr:
    .quad 0

.align 8
ap_gs_base:
    .quad 0

.align 8
ap_entry_point:
    .quad 0

.section .note.GNU-stack,"",@progbits
