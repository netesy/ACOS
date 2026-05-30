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
}

} // namespace acos::hal
