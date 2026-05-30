#pragma once
#include <acos/types.h>

namespace acos::ipc {

/**
 * SharedRegion represents a physical memory range that can be mapped into multiple address spaces.
 * It tracks physical pages rather than just virtual pointers.
 */
class SharedRegion {
public:
    SharedRegion(u64 physical_addr, usize size);

    u64 physical_addr() const { return m_physical_addr; }
    usize size() const { return m_size; }
    u64 id() const { return m_id; }

    // Future: Track which processes have this region mapped
    // bool map_into(Process* p, u64 virtual_addr);

private:
    u64 m_id;
    u64 m_physical_addr;
    usize m_size;
};

} // namespace acos::ipc
