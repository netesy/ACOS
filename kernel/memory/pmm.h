#pragma once
#include <acos/types.h>
#include <acos/boot_info.h>

namespace acos::memory {
    void pmm_init(BootInfo* bootInfo);
    u64 pmm_alloc();
    void pmm_free(u64 addr);
}
