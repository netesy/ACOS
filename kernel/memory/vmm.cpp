#include <acos/types.h>
#include <kernel/memory/pmm.h>
#include <kernel/hal/serial.h>

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

static PageTable* alloc_table() {
    u64 addr = pmm_alloc();
    if (addr == 0) return nullptr;
    auto* table = reinterpret_cast<PageTable*>(addr);
    clear_page_table(table);
    return table;
}

// Map a single 4KB page
void vmm_map(PageTable* pml4, u64 virt, u64 phys, u64 flags) {
    u64 pml4_idx = (virt >> 39) & 0x1FF;
    u64 pdpt_idx = (virt >> 30) & 0x1FF;
    u64 pd_idx   = (virt >> 21) & 0x1FF;
    u64 pt_idx   = (virt >> 12) & 0x1FF;

    if (!(pml4->entries[pml4_idx] & 1)) {
        PageTable* t = alloc_table();
        if (!t) return;
        pml4->entries[pml4_idx] = reinterpret_cast<u64>(t) | 3;
    }
    auto* pdpt = reinterpret_cast<PageTable*>(pml4->entries[pml4_idx] & ~0xFFFULL);

    if (!(pdpt->entries[pdpt_idx] & 1)) {
        PageTable* t = alloc_table();
        if (!t) return;
        pdpt->entries[pdpt_idx] = reinterpret_cast<u64>(t) | 3;
    }
    auto* pd = reinterpret_cast<PageTable*>(pdpt->entries[pdpt_idx] & ~0xFFFULL);

    if (!(pd->entries[pd_idx] & 1)) {
        PageTable* t = alloc_table();
        if (!t) return;
        pd->entries[pd_idx] = reinterpret_cast<u64>(t) | 3;
    }
    auto* pt = reinterpret_cast<PageTable*>(pd->entries[pd_idx] & ~0xFFFULL);

    pt->entries[pt_idx] = phys | flags | 1;
}

// Map a 2MB large page (PS bit set in PD entry) — much faster for bulk mapping
static void vmm_map_2m(PageTable* pml4, u64 virt, u64 phys, u64 flags) {
    u64 pml4_idx = (virt >> 39) & 0x1FF;
    u64 pdpt_idx = (virt >> 30) & 0x1FF;
    u64 pd_idx   = (virt >> 21) & 0x1FF;

    if (!(pml4->entries[pml4_idx] & 1)) {
        PageTable* t = alloc_table();
        if (!t) return;
        pml4->entries[pml4_idx] = reinterpret_cast<u64>(t) | 3;
    }
    auto* pdpt = reinterpret_cast<PageTable*>(pml4->entries[pml4_idx] & ~0xFFFULL);

    if (!(pdpt->entries[pdpt_idx] & 1)) {
        PageTable* t = alloc_table();
        if (!t) return;
        pdpt->entries[pdpt_idx] = reinterpret_cast<u64>(t) | 3;
    }
    auto* pd = reinterpret_cast<PageTable*>(pdpt->entries[pdpt_idx] & ~0xFFFULL);

    // Set PD entry with PS (Page Size) bit 7 for 2MB page
    pd->entries[pd_idx] = phys | flags | 1 | (1ULL << 7);
}

void vmm_init(BootInfo* bootInfo) {
    g_kernel_pml4 = reinterpret_cast<PageTable*>(pmm_alloc());
    if (!g_kernel_pml4) {
        acos::hal::serial_print("[VMM] ERROR: pmm_alloc for PML4 failed\n");
        return;
    }
    clear_page_table(g_kernel_pml4);

    // Identity-map physical memory using 2MB large pages for speed
    u64 phys_limit = pmm_get_total_memory();
    if (phys_limit == 0) phys_limit = 0x40000000;
    if (phys_limit > 0x100000000ULL) phys_limit = 0x100000000ULL;

    // Round up to 2MB boundary
    u64 map_limit = (phys_limit + 0x1FFFFF) & ~0x1FFFFFULL;

    for (u64 addr = 0; addr < map_limit; addr += 0x200000) {
        vmm_map_2m(g_kernel_pml4, addr, addr, 3); // Present + Writable
    }

    // Map framebuffer region with 2MB pages
    if (bootInfo && bootInfo->framebuffer && bootInfo->framebuffer->base != 0 && bootInfo->framebuffer->size != 0) {
        const u64 start = bootInfo->framebuffer->base & ~0x1FFFFFULL;
        const u64 end = (bootInfo->framebuffer->base + bootInfo->framebuffer->size + 0x1FFFFF) & ~0x1FFFFFULL;
        for (u64 addr = start; addr < end; addr += 0x200000) {
            vmm_map_2m(g_kernel_pml4, addr, addr, 3);
        }
    }

    acos::hal::serial_print("[VMM] CR3 loaded\n");
    __asm__ volatile("mov %0, %%cr3" : : "r"(g_kernel_pml4));
}

} // namespace acos::memory
