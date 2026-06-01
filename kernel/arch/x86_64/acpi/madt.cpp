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

} // namespace acos::arch::x86_64
