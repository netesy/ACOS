#pragma once
#include <kernel/memory/paging.h>
#include <acos/boot_info.h>

namespace acos::memory {

// Virtual memory management functions
void vmm_init(BootInfo* bootInfo);
void vmm_map(PageTable* pml4, u64 virt, u64 phys, u64 flags);

// W^X Page-table validation
bool vmm_validate_wx();

} // namespace acos::memory
