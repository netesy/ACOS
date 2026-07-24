#include "madt.h"
#include <libs/runtime/include/acos/runtime.h>

namespace acos::arch::x86_64 {

u32 MADT::g_apic_ids[64];
u32 MADT::g_cpu_count = 0;

bool MADT::parse(void* table_ptr) {
    if (!table_ptr) return false;

    MADTHeader* header = (MADTHeader*)table_ptr;
    u8* ptr = (u8*)(header + 1);
    u8* end = (u8*)table_ptr + header->length;

    while (ptr < end) {
        u8 type = ptr[0];
        u8 len = ptr[1];

        if (type == 0) { // Processor Local APIC
            u8 apic_id = ptr[3];
            u32 flags = *(u32*)(ptr + 4);
            if (flags & 1) { // Enabled
                if (g_cpu_count < 64) {
                    g_apic_ids[g_cpu_count++] = apic_id;
                }
            }
        }
        ptr += len;
    }
    return true;
}

static bool compare_sig(const char* s1, const char* s2, usize len) {
    for (usize i = 0; i < len; i++) {
        if (s1[i] != s2[i]) return false;
    }
    return true;
}

void* MADT::find_table(void* rsdp_ptr, const char* signature) {
    if (!rsdp_ptr || !signature) return nullptr;

    RSDPDescriptor* rsdp = (RSDPDescriptor*)rsdp_ptr;
    if (!compare_sig(rsdp->signature, "RSD PTR ", 8)) return nullptr;

    bool use_xsdt = false;
    u64 sdt_address = rsdp->rsdt_address;

    if (rsdp->revision >= 2) {
        RSDPDescriptor20* rsdp20 = (RSDPDescriptor20*)rsdp_ptr;
        if (rsdp20->xsdt_address != 0) {
            sdt_address = rsdp20->xsdt_address;
            use_xsdt = true;
        }
    }

    if (sdt_address == 0) return nullptr;

    ACPISDTHeader* sdt_header = (ACPISDTHeader*)sdt_address;

    if (use_xsdt) {
        XSDT* xsdt = (XSDT*)sdt_address;
        usize entries = (sdt_header->length - sizeof(ACPISDTHeader)) / sizeof(u64);
        for (usize i = 0; i < entries; i++) {
            ACPISDTHeader* table = (ACPISDTHeader*)xsdt->pointer_to_other_sdt[i];
            if (table && compare_sig(table->signature, signature, 4)) {
                return table;
            }
        }
    } else {
        RSDT* rsdt = (RSDT*)sdt_address;
        usize entries = (sdt_header->length - sizeof(ACPISDTHeader)) / sizeof(u32);
        for (usize i = 0; i < entries; i++) {
            ACPISDTHeader* table = (ACPISDTHeader*)((u64)rsdt->pointer_to_other_sdt[i]);
            if (table && compare_sig(table->signature, signature, 4)) {
                return table;
            }
        }
    }

    return nullptr;
}

} // namespace acos::arch::x86_64
