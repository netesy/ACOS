#pragma once
#include <acos/types.h>

namespace acos::hal {
    void gdt_init();
    void tss_set_rsp0(u64 rsp0);
}
