#include <acos/types.h>
#include <kernel/memory/pmm.h>

namespace acos::memory {

struct PageTable {
    u64 entries[512];
} __attribute__((aligned(4096)));

static PageTable* g_kernel_pml4 = nullptr;

void vmm_map(PageTable* pml4, u64 virt, u64 phys, u64 flags) {
    u64 pml4_idx = (virt >> 39) & 0x1FF;
    u64 pdpt_idx = (virt >> 30) & 0x1FF;
    u64 pd_idx   = (virt >> 21) & 0x1FF;
    u64 pt_idx   = (virt >> 12) & 0x1FF;

    auto get_next_level = [](u64* entry) -> PageTable* {
        if (!(*entry & 1)) {
            u64 addr = pmm_alloc();
            *entry = addr | 3; // Present + Writable
            return reinterpret_cast<PageTable*>(addr);
        }
        return reinterpret_cast<PageTable*>(*entry & ~0xFFFULL);
    };

    PageTable* pdpt = get_next_level(&pml4->entries[pml4_idx]);
    PageTable* pd   = get_next_level(&pdpt->entries[pdpt_idx]);
    PageTable* pt   = get_next_level(&pd->entries[pd_idx]);

    pt->entries[pt_idx] = phys | flags | 1;
}

void vmm_init() {
    g_kernel_pml4 = reinterpret_cast<PageTable*>(pmm_alloc());
    for(int i=0; i<512; i++) g_kernel_pml4->entries[i] = 0;

    for (u64 addr = 0; addr < 0x40000000; addr += 4096) {
        vmm_map(g_kernel_pml4, addr, addr, 3);
    }

    __asm__ volatile("mov %0, %%cr3" : : "r"(g_kernel_pml4));
}

} // namespace acos::memory
