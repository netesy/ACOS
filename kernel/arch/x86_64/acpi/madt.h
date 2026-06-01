#pragma once
#include <acos/types.h>

namespace acos::arch::x86_64 {

struct MADTHeader {
    char signature[4];
    u32 length;
    u8 revision;
    u8 checksum;
    char oem_id[6];
    char oem_table_id[8];
    u32 oem_revision;
    u32 creator_id;
    u32 creator_revision;
    u32 lapic_addr;
    u32 flags;
} __attribute__((packed));

class MADT {
public:
    static bool parse(void* table_ptr);
    static u32 cpu_count() { return g_cpu_count; }
    static u32 get_apic_id(u32 index) { return g_apic_ids[index]; }

private:
    static u32 g_apic_ids[64];
    static u32 g_cpu_count;
};

} // namespace acos::arch::x86_64
