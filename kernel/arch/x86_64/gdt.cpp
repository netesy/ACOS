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

struct TSSEntry {
    u32 reserved0;
    u64 rsp0;
    u64 rsp1;
    u64 rsp2;
    u64 reserved1;
    u64 ist1;
    u64 ist2;
    u64 ist3;
    u64 ist4;
    u64 ist5;
    u64 ist6;
    u64 ist7;
    u64 reserved2;
    u16 reserved3;
    u16 iopb_offset;
} __attribute__((packed));

static GDTEntry g_gdt[7];
static GDTPointer g_gdt_ptr;
static TSSEntry g_tss;

void gdt_init() {
    // 0: Null
    g_gdt[0] = {0, 0, 0, 0, 0, 0};
    // 1: Kernel Code (0x08)
    g_gdt[1] = {0, 0, 0, 0x9A, 0x20, 0};
    // 2: Kernel Data (0x10)
    g_gdt[2] = {0, 0, 0, 0x92, 0x00, 0};
    // 3: User Data   (0x18)
    g_gdt[3] = {0, 0, 0, 0xF2, 0x00, 0};
    // 4: User Code   (0x20)
    g_gdt[4] = {0, 0, 0, 0xFA, 0x20, 0};

    // 5-6: TSS (System segment, 16 bytes)
    u64 tss_base = reinterpret_cast<u64>(&g_tss);
    u32 tss_limit = sizeof(g_tss) - 1;

    g_gdt[5].limit_low = tss_limit & 0xFFFF;
    g_gdt[5].base_low = tss_base & 0xFFFF;
    g_gdt[5].base_middle = (tss_base >> 16) & 0xFF;
    g_gdt[5].access = 0x89;
    g_gdt[5].granularity = (tss_limit >> 16) & 0x0F;
    g_gdt[5].base_high = (tss_base >> 24) & 0xFF;

    *reinterpret_cast<u64*>(&g_gdt[6]) = tss_base >> 32;

    g_gdt_ptr.limit = sizeof(g_gdt) - 1;
    g_gdt_ptr.base = reinterpret_cast<u64>(&g_gdt);

    __asm__ volatile("lgdt %0" : : "m"(g_gdt_ptr));
    __asm__ volatile("ltr %%ax" : : "a"(static_cast<u16>(0x28)));
}

} // namespace acos::hal
