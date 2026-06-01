#include <acos/types.h>
#include <kernel/memory/pmm.h>

namespace acos::memory {

struct PageTable {
    u64 entries[512];
} __attribute__((aligned(4096)));

static PageTable* g_kernel_pml4 = nullptr;

void clear_page_table(PageTable* table) {
    if (!table) return;
    for (int i = 0; i < 512; ++i) {
        table->entries[i] = 0;
    }
}

void vmm_map(PageTable* pml4, u64 virt, u64 phys, u64 flags) {
    u64 pml4_idx = (virt >> 39) & 0x1FF;
    u64 pdpt_idx = (virt >> 30) & 0x1FF;
    u64 pd_idx   = (virt >> 21) & 0x1FF;
    u64 pt_idx   = (virt >> 12) & 0x1FF;

    auto get_next_level = [](u64* entry) -> PageTable* {
        if (!(*entry & 1)) {
            u64 addr = pmm_alloc();
            if (addr == 0) {
                return nullptr;
            }
            auto* table = reinterpret_cast<PageTable*>(addr);
            clear_page_table(table);
            *entry = addr | 3; // Present + Writable
            return table;
        }
        return reinterpret_cast<PageTable*>(*entry & ~0xFFFULL);
    };

    PageTable* pdpt = get_next_level(&pml4->entries[pml4_idx]);
    if (!pdpt) return;
    PageTable* pd   = get_next_level(&pdpt->entries[pdpt_idx]);
    if (!pd) return;
    PageTable* pt   = get_next_level(&pd->entries[pd_idx]);
    if (!pt) return;

    pt->entries[pt_idx] = phys | flags | 1;
}

void vmm_init(BootInfo* bootInfo) {
    g_kernel_pml4 = reinterpret_cast<PageTable*>(pmm_alloc());
    if (!g_kernel_pml4) {
        return;
    }
    clear_page_table(g_kernel_pml4);

    for (u64 addr = 0; addr < 0x40000000; addr += 4096) {
        vmm_map(g_kernel_pml4, addr, addr, 3);
    }

    if (bootInfo && bootInfo->framebuffer && bootInfo->framebuffer->base != 0 && bootInfo->framebuffer->size != 0) {
        const u64 start = bootInfo->framebuffer->base & ~0xFFFULL;
        const u64 end = (bootInfo->framebuffer->base + bootInfo->framebuffer->size + 0xFFFULL) & ~0xFFFULL;
        for (u64 addr = start; addr < end; addr += 4096) {
            vmm_map(g_kernel_pml4, addr, addr, 3);
        }
    }

    __asm__ volatile("mov %0, %%cr3" : : "r"(g_kernel_pml4));
}

} // namespace acos::memory
