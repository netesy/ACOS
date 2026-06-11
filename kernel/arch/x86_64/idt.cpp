#include <acos/types.h>

namespace acos::hal {

struct IDTEntry {
    u16 base_low;
    u16 selector;
    u8 ist;
    u8 flags;
    u16 base_mid;
    u32 base_high;
    u32 reserved;
} __attribute__((packed));

struct IDTPointer {
    u16 limit;
    u64 base;
} __attribute__((packed));

static IDTEntry g_idt[256];
static IDTPointer g_idt_ptr;

extern "C" void syscall_entry();

void idt_set_gate(u8 num, u64 base, u16 selector, u8 flags) {
    g_idt[num].base_low = base & 0xFFFF;
    g_idt[num].base_mid = (base >> 16) & 0xFFFF;
    g_idt[num].base_high = (base >> 32) & 0xFFFFFFFF;
    g_idt[num].selector = selector;
    g_idt[num].ist = 0;
    g_idt[num].flags = flags;
    g_idt[num].reserved = 0;
}

void idt_init() {
    g_idt_ptr.limit = sizeof(g_idt) - 1;
    g_idt_ptr.base = reinterpret_cast<u64>(&g_idt);

    // Initialise with dummy handlers
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0x08, 0x8E);
    }

    __asm__ volatile("lidt %0" : : "m"(g_idt_ptr));

    // Initialize Syscall MSRs
    u32 low, high;

    // EFER: Enable SCE (System Call Extensions)
    __asm__ volatile("rdmsr" : "=a"(low), "=d"(high) : "c"(0xC0000080));
    low |= 1;
    __asm__ volatile("wrmsr" : : "c"(0xC0000080), "a"(low), "d"(high));

    // STAR: Kernel CS 0x08, User Base 0x13 (for SYSRET)
    // STAR[47:32] = Kernel CS (0x08)
    // STAR[63:48] = User Base (0x13)
    // SYSRET sets: SS = 0x13 + 8 = 0x1B (User Data), CS = 0x13 + 16 = 0x23 (User Code)
    low = 0;
    high = (0x13 << 16) | 0x08;
    __asm__ volatile("wrmsr" : : "c"(0xC0000081), "a"(low), "d"(high));

    // LSTAR: Syscall Entry Point
    u64 entry = reinterpret_cast<u64>(syscall_entry);
    low = static_cast<u32>(entry);
    high = static_cast<u32>(entry >> 32);
    __asm__ volatile("wrmsr" : : "c"(0xC0000082), "a"(low), "d"(high));

    // SFMASK: Disable interrupts on syscall entry
    low = 0x200; // IF bit
    high = 0;
    __asm__ volatile("wrmsr" : : "c"(0xC0000084), "a"(low), "d"(high));
}

} // namespace acos::hal
