#pragma once
#include <acos/types.h>

namespace acos::arch::x86_64 {

struct RSDPDescriptor {
    char signature[8];
    u8 checksum;
    char oem_id[6];
    u8 revision;
    u32 rsdt_address;
} __attribute__((packed));

struct RSDPDescriptor20 {
    RSDPDescriptor firstPart;
    u32 length;
    u64 xsdt_address;
    u8 extended_checksum;
    u8 reserved[3];
} __attribute__((packed));

struct ACPISDTHeader {
    char signature[4];
    u32 length;
    u8 revision;
    u8 checksum;
    char oem_id[6];
    char oem_table_id[8];
    u32 oem_revision;
    u32 creator_id;
    u32 creator_revision;
} __attribute__((packed));

struct RSDT {
    ACPISDTHeader h;
    u32 pointer_to_other_sdt[128]; // Mapped placeholder
} __attribute__((packed));

struct XSDT {
    ACPISDTHeader h;
    u64 pointer_to_other_sdt[128]; // Mapped placeholder
} __attribute__((packed));

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
    static void* find_table(void* rsdp_ptr, const char* signature);
    static u32 cpu_count() { return g_cpu_count; }
    static u32 get_apic_id(u32 index) { return g_apic_ids[index]; }

private:
    static u32 g_apic_ids[64];
    static u32 g_cpu_count;
};

} // namespace acos::arch::x86_64
