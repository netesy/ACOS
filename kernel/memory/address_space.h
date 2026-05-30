#pragma once
#include <acos/types.h>
#include <kernel/memory/paging.h>

namespace acos::memory {

class AddressSpace {
public:
    AddressSpace();
    ~AddressSpace();

    bool map(u64 virt, u64 phys, u64 flags);
    bool unmap(u64 virt);
    bool protect(u64 virt, u64 flags);
    u64 translate(u64 virt);

    u64 pml4_phys() const { return m_pml4_phys; }

private:
    u64 m_pml4_phys;
    PageTable* m_pml4_virt;
};

} // namespace acos::memory
