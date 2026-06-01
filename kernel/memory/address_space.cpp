#include <kernel/memory/address_space.h>
#include <kernel/memory/pmm.h>
#include <acos/runtime.h>

namespace acos::memory {

AddressSpace::AddressSpace() {
    m_pml4_phys = pmm_alloc();
    if (m_pml4_phys == 0) {
        // Halt if we can't even create an address space root
        while(1) { __asm__("hlt"); }
    }
    m_pml4_virt = reinterpret_cast<PageTable*>(m_pml4_phys);
    for(int i=0; i<512; i++) m_pml4_virt->entries[i] = 0;

    // Identity map first 1GB
    for (u64 addr = 0; addr < 0x40000000; addr += 4096) {
        map(addr, addr, PageFlags::Present | PageFlags::Writable);
    }
}

AddressSpace::~AddressSpace() {
    // Recursively free all page tables
    if (m_pml4_virt) {
        for (int i = 0; i < 512; i++) {
            if (m_pml4_virt->entries[i] & PageFlags::Present) {
                u64 pdpt_phys = m_pml4_virt->entries[i] & ~0xFFFULL;
                PageTable* pdpt = reinterpret_cast<PageTable*>(pdpt_phys);
                
                for (int j = 0; j < 512; j++) {
                    if (pdpt->entries[j] & PageFlags::Present) {
                        u64 pd_phys = pdpt->entries[j] & ~0xFFFULL;
                        PageTable* pd = reinterpret_cast<PageTable*>(pd_phys);
                        
                        for (int k = 0; k < 512; k++) {
                            if (pd->entries[k] & PageFlags::Present) {
                                u64 pt_phys = pd->entries[k] & ~0xFFFULL;
                                PageTable* pt [[maybe_unused]] = reinterpret_cast<PageTable*>(pt_phys);
                                
                                // Free page table
                                pmm_free(pt_phys);
                            }
                        }
                        
                        // Free page directory
                        pmm_free(pd_phys);
                    }
                }
                
                // Free PDPT
                pmm_free(pdpt_phys);
            }
        }
        
        // Free PML4
        pmm_free(m_pml4_phys);
    }
}

bool AddressSpace::map(u64 virt, u64 phys, u64 flags) {
    u64 pml4_idx = (virt >> 39) & 0x1FF;
    u64 pdpt_idx = (virt >> 30) & 0x1FF;
    u64 pd_idx   = (virt >> 21) & 0x1FF;
    u64 pt_idx   = (virt >> 12) & 0x1FF;

    auto get_next_level = [](u64* entry) -> PageTable* {
        if (!(*entry & PageFlags::Present)) {
            u64 addr = pmm_alloc();
            if (addr == 0) return nullptr;
            *entry = addr | PageFlags::Present | PageFlags::Writable | PageFlags::User;
            PageTable* pt = reinterpret_cast<PageTable*>(addr);
            for(int i=0; i<512; i++) pt->entries[i] = 0;
            return pt;
        }
        return reinterpret_cast<PageTable*>(*entry & ~0xFFFULL);
    };

    PageTable* pdpt = get_next_level(&m_pml4_virt->entries[pml4_idx]);
    if (!pdpt) return false;
    PageTable* pd   = get_next_level(&pdpt->entries[pdpt_idx]);
    if (!pd) return false;
    PageTable* pt   = get_next_level(&pd->entries[pd_idx]);
    if (!pt) return false;

    pt->entries[pt_idx] = phys | flags | PageFlags::Present;
    return true;
}

bool AddressSpace::unmap(u64 virt) {
    u64 pml4_idx = (virt >> 39) & 0x1FF;
    u64 pdpt_idx = (virt >> 30) & 0x1FF;
    u64 pd_idx   = (virt >> 21) & 0x1FF;
    u64 pt_idx   = (virt >> 12) & 0x1FF;

    if (!(m_pml4_virt->entries[pml4_idx] & PageFlags::Present)) return false;
    PageTable* pdpt = reinterpret_cast<PageTable*>(m_pml4_virt->entries[pml4_idx] & ~0xFFFULL);

    if (!(pdpt->entries[pdpt_idx] & PageFlags::Present)) return false;
    PageTable* pd = reinterpret_cast<PageTable*>(pdpt->entries[pdpt_idx] & ~0xFFFULL);

    if (!(pd->entries[pd_idx] & PageFlags::Present)) return false;
    PageTable* pt = reinterpret_cast<PageTable*>(pd->entries[pd_idx] & ~0xFFFULL);

    pt->entries[pt_idx] = 0;
    __asm__ volatile("invlpg (%0)" : : "r"(virt) : "memory");
    return true;
}

u64 AddressSpace::translate(u64 virt) {
    u64 pml4_idx = (virt >> 39) & 0x1FF;
    u64 pdpt_idx = (virt >> 30) & 0x1FF;
    u64 pd_idx   = (virt >> 21) & 0x1FF;
    u64 pt_idx   = (virt >> 12) & 0x1FF;

    if (!(m_pml4_virt->entries[pml4_idx] & PageFlags::Present)) return 0;
    PageTable* pdpt = reinterpret_cast<PageTable*>(m_pml4_virt->entries[pml4_idx] & ~0xFFFULL);

    if (!(pdpt->entries[pdpt_idx] & PageFlags::Present)) return 0;
    PageTable* pd = reinterpret_cast<PageTable*>(pdpt->entries[pdpt_idx] & ~0xFFFULL);

    if (!(pd->entries[pd_idx] & PageFlags::Present)) return 0;
    PageTable* pt = reinterpret_cast<PageTable*>(pd->entries[pd_idx] & ~0xFFFULL);

    return (pt->entries[pt_idx] & ~0xFFFULL) | (virt & 0xFFF);
}

} // namespace acos::memory
