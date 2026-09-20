#include <kernel/memory/address_space.h>
#include <kernel/memory/pmm.h>
#include <acos/runtime.h>

namespace acos::memory {

AddressSpace::AddressSpace() {
    m_pml4_phys = pmm_alloc();
    if (m_pml4_phys == 0) {
        while(1) { __asm__("hlt"); }
    }
    m_pml4_virt = reinterpret_cast<PageTable*>(m_pml4_phys);
    for(int i=0; i<512; i++) m_pml4_virt->entries[i] = 0;

    // Identity map first 4GB to ensure kernel and MMIO are always accessible
    for (u64 addr = 0; addr < 0x100000000ULL; addr += 0x200000) {
        u64 pml4_idx = (addr >> 39) & 0x1FF;
        u64 pdpt_idx = (addr >> 30) & 0x1FF;
        u64 pd_idx   = (addr >> 21) & 0x1FF;

        auto get_next_level = [](u64* entry) -> PageTable* {
            if (!(*entry & 1)) {
                u64 addr = pmm_alloc();
                if (addr == 0) return nullptr;
                *entry = addr | 3;
                PageTable* pt = reinterpret_cast<PageTable*>(addr);
                for(int i=0; i<512; i++) pt->entries[i] = 0;
                return pt;
            }
            return reinterpret_cast<PageTable*>(*entry & ~0xFFFULL);
        };

        PageTable* pdpt = get_next_level(&m_pml4_virt->entries[pml4_idx]);
        PageTable* pd   = get_next_level(&pdpt->entries[pdpt_idx]);
        pd->entries[pd_idx] = addr | 0x83; // Present, Writable, Huge Page
    }
}

AddressSpace::~AddressSpace() {
    if (m_pml4_virt) {
        for (int i = 0; i < 512; i++) {
            if (m_pml4_virt->entries[i] & 1) {
                u64 pdpt_phys = m_pml4_virt->entries[i] & ~0xFFFULL;
                PageTable* pdpt = reinterpret_cast<PageTable*>(pdpt_phys);
                for (int j = 0; j < 512; j++) {
                    if (pdpt->entries[j] & 1) {
                        u64 pd_phys = pdpt->entries[j] & ~0xFFFULL;
                        PageTable* pd = reinterpret_cast<PageTable*>(pd_phys);
                        for (int k = 0; k < 512; k++) {
                            if ((pd->entries[k] & 1) && !(pd->entries[k] & 0x80)) {
                                u64 pt_phys = pd->entries[k] & ~0xFFFULL;
                                pmm_free(pt_phys);
                            }
                        }
                        pmm_free(pd_phys);
                    }
                }
                pmm_free(pdpt_phys);
            }
        }
        pmm_free(m_pml4_phys);
    }
}

bool AddressSpace::map(u64 virt, u64 phys, u64 flags) {
    u64 pml4_idx = (virt >> 39) & 0x1FF;
    u64 pdpt_idx = (virt >> 30) & 0x1FF;
    u64 pd_idx   = (virt >> 21) & 0x1FF;
    u64 pt_idx   = (virt >> 12) & 0x1FF;

    auto get_next_level = [](u64* entry, bool is_user) -> PageTable* {
        if (!(*entry & 1)) {
            u64 addr = pmm_alloc();
            if (addr == 0) return nullptr;
            *entry = addr | 3 | (is_user ? 4 : 0); // Present, Writable, User
            PageTable* pt = reinterpret_cast<PageTable*>(addr);
            for(int i=0; i<512; i++) pt->entries[i] = 0;
            return pt;
        }
        if (is_user) *entry |= 4;

        if (*entry & 0x80) { // Huge Page (2MB) - need to split it
            u64 huge_phys = *entry & ~0x1FFFFFULL;
            u64 huge_flags = *entry & 0x1FFFFFULL & ~0x80ULL;
            u64 addr = pmm_alloc();
            if (addr == 0) return nullptr;
            PageTable* pt = reinterpret_cast<PageTable*>(addr);
            for(int i=0; i<512; i++) {
                pt->entries[i] = (huge_phys + (i * 4096)) | huge_flags;
            }
            *entry = addr | 3 | (is_user ? 4 : 0);
            return pt;
        }

        return reinterpret_cast<PageTable*>(*entry & ~0xFFFULL);
    };

    bool is_user = (flags & 4) != 0;
    PageTable* pdpt = get_next_level(&m_pml4_virt->entries[pml4_idx], is_user);
    if (!pdpt) return false;
    PageTable* pd   = get_next_level(&pdpt->entries[pdpt_idx], is_user);
    if (!pd) return false;
    PageTable* pt   = get_next_level(&pd->entries[pd_idx], is_user);
    if (!pt) return false;

    pt->entries[pt_idx] = phys | flags | 1;

    // Only invalidate TLB if this address space is currently active
    u64 current_cr3;
    __asm__ volatile("mov %%cr3, %0" : "=r"(current_cr3));
    if ((current_cr3 & ~0xFFFULL) == m_pml4_phys) {
        __asm__ volatile("invlpg (%0)" : : "r"(virt) : "memory");
    }
    return true;
}

bool AddressSpace::unmap(u64 virt) {
    u64 pml4_idx = (virt >> 39) & 0x1FF;
    u64 pdpt_idx = (virt >> 30) & 0x1FF;
    u64 pd_idx   = (virt >> 21) & 0x1FF;
    u64 pt_idx   = (virt >> 12) & 0x1FF;

    if (!(m_pml4_virt->entries[pml4_idx] & 1)) return false;
    PageTable* pdpt = reinterpret_cast<PageTable*>(m_pml4_virt->entries[pml4_idx] & ~0xFFFULL);
    if (!(pdpt->entries[pdpt_idx] & 1)) return false;
    PageTable* pd = reinterpret_cast<PageTable*>(pdpt->entries[pdpt_idx] & ~0xFFFULL);
    if (!(pd->entries[pd_idx] & 1)) return false;
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

    if (!(m_pml4_virt->entries[pml4_idx] & 1)) return 0;
    PageTable* pdpt = reinterpret_cast<PageTable*>(m_pml4_virt->entries[pml4_idx] & ~0xFFFULL);
    if (!(pdpt->entries[pdpt_idx] & 1)) return 0;
    PageTable* pd = reinterpret_cast<PageTable*>(pdpt->entries[pdpt_idx] & ~0xFFFULL);
    if (!(pd->entries[pd_idx] & 1)) return 0;
    if (pd->entries[pd_idx] & 0x80) return (pd->entries[pd_idx] & ~0x1FFFFFULL) | (virt & 0x1FFFFF);
    PageTable* pt = reinterpret_cast<PageTable*>(pd->entries[pd_idx] & ~0xFFFULL);

    return (pt->entries[pt_idx] & ~0xFFFULL) | (virt & 0xFFF);
}

AddressSpace* AddressSpace::clone() {
    AddressSpace* child = new AddressSpace();
    if (!child) return nullptr;

    auto alloc_table_clean = []() -> PageTable* {
        u64 phys = pmm_alloc();
        if (phys == 0) return nullptr;
        PageTable* pt = reinterpret_cast<PageTable*>(phys);
        for (int idx = 0; idx < 512; idx++) pt->entries[idx] = 0;
        return pt;
    };

    // Walk the user-space portion of the PML4 (indices 0 to 255)
    for (int i = 0; i < 256; i++) {
        u64 pml4e = m_pml4_virt->entries[i];
        if (!(pml4e & 1) || !(pml4e & 4)) continue;

        PageTable* parent_pdpt = reinterpret_cast<PageTable*>(pml4e & ~0xFFFULL);
        PageTable* child_pdpt = nullptr;

        for (int j = 0; j < 512; j++) {
            u64 pdpte = parent_pdpt->entries[j];
            if (!(pdpte & 1) || !(pdpte & 4) || (pdpte & 0x80)) continue;

            PageTable* parent_pd = reinterpret_cast<PageTable*>(pdpte & ~0xFFFULL);
            PageTable* child_pd = nullptr;

            for (int k = 0; k < 512; k++) {
                u64 pde = parent_pd->entries[k];
                if (!(pde & 1) || !(pde & 4) || (pde & 0x80)) continue;

                PageTable* parent_pt = reinterpret_cast<PageTable*>(pde & ~0xFFFULL);
                PageTable* child_pt = nullptr;

                for (int l = 0; l < 512; l++) {
                    u64 entry = parent_pt->entries[l];
                    if (!(entry & 1) || !(entry & 4)) continue;

                    u64 phys = entry & ~0xFFFULL & ~0xFFF0000000000000ULL;

                    if (entry & 2) { // Writable
                        entry &= ~2ULL; // Clear Writable
                        entry |= (1ULL << 9); // Set COW bit
                        parent_pt->entries[l] = entry;
                    }

                    // Lazily construct child page table hierarchy directly
                    if (!child_pdpt) {
                        child_pdpt = alloc_table_clean();
                        if (!child_pdpt) return nullptr;
                        child->m_pml4_virt->entries[i] = reinterpret_cast<u64>(child_pdpt) | (pml4e & 0xFFFULL);
                    }
                    if (!child_pd) {
                        child_pd = alloc_table_clean();
                        if (!child_pd) return nullptr;
                        child_pdpt->entries[j] = reinterpret_cast<u64>(child_pd) | (pdpte & 0xFFFULL);
                    }
                    if (!child_pt) {
                        child_pt = alloc_table_clean();
                        if (!child_pt) return nullptr;
                        child_pd->entries[k] = reinterpret_cast<u64>(child_pt) | (pde & 0xFFFULL);
                    }

                    child_pt->entries[l] = entry;
                    pmm_inc_ref_count(phys / 4096);
                }
            }
        }
    }

    // Flush TLB for current active CR3
    u64 current_cr3;
    __asm__ volatile("mov %%cr3, %0" : "=r"(current_cr3));
    if ((current_cr3 & ~0xFFFULL) == m_pml4_phys) {
        __asm__ volatile("mov %0, %%cr3" : : "r"(current_cr3) : "memory");
    }

    return child;
}

u64* AddressSpace::get_pte_ptr(u64 virt) {
    u64 pml4_idx = (virt >> 39) & 0x1FF;
    u64 pdpt_idx = (virt >> 30) & 0x1FF;
    u64 pd_idx   = (virt >> 21) & 0x1FF;
    u64 pt_idx   = (virt >> 12) & 0x1FF;

    if (!(m_pml4_virt->entries[pml4_idx] & 1)) return nullptr;
    PageTable* pdpt = reinterpret_cast<PageTable*>(m_pml4_virt->entries[pml4_idx] & ~0xFFFULL);
    if (!(pdpt->entries[pdpt_idx] & 1)) return nullptr;
    PageTable* pd = reinterpret_cast<PageTable*>(pdpt->entries[pdpt_idx] & ~0xFFFULL);
    if (!(pd->entries[pd_idx] & 1)) return nullptr;
    if (pd->entries[pd_idx] & 0x80) return nullptr;
    PageTable* pt = reinterpret_cast<PageTable*>(pd->entries[pd_idx] & ~0xFFFULL);

    return &pt->entries[pt_idx];
}

} // namespace acos::memory
