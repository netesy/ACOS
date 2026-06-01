#pragma once
#include <kernel/memory/paging.h>

namespace acos::memory {

// Virtual memory management functions
void vmm_init();
void vmm_map(PageTable* pml4, u64 virt, u64 phys, u64 flags);

} // namespace acos::memory
