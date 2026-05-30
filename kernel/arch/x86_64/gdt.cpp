#include <acos/types.h>

namespace acos::hal {

struct GDTEntry {
    u16 limit_low;
    u16 base_low;
    u8 base_middle;
    u8 access;
    u8 granularity;
    u8 base_high;
} __attribute__((packed));

struct GDTPointer {
    u16 limit;
    u64 base;
} __attribute__((packed));

static GDTEntry g_gdt[5];
static GDTPointer g_gdt_ptr;

void gdt_init() {
    // Null segment
    g_gdt[0] = {0, 0, 0, 0, 0, 0};
    // Kernel Code (64-bit)
    g_gdt[1] = {0, 0, 0, 0x9A, 0x20, 0};
    // Kernel Data
    g_gdt[2] = {0, 0, 0, 0x92, 0x00, 0};
    // User Code
    g_gdt[3] = {0, 0, 0, 0xFA, 0x20, 0};
    // User Data
    g_gdt[4] = {0, 0, 0, 0xF2, 0x00, 0};

    g_gdt_ptr.limit = sizeof(g_gdt) - 1;
    g_gdt_ptr.base = reinterpret_cast<u64>(&g_gdt);

    __asm__ volatile("lgdt %0" : : "m"(g_gdt_ptr));
}

} // namespace acos::hal
