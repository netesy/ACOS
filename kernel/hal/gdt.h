#pragma once
#include <acos/types.h>

namespace acos::hal {
    void gdt_init();
    void gdt_init_cpu(u32 cpu_index);
    void tss_set_rsp0(u64 rsp0);
}
