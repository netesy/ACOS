#pragma once
#include <acos/types.h>

namespace acos::ipc {

class SharedRegion {
public:
    SharedRegion(u64 physical_addr, usize size);

    u64 physical_addr() const { return m_physical_addr; }
    usize size() const { return m_size; }
    u64 id() const { return m_id; }
    u64 owner() const { return m_owner; }

private:
    u64 m_id;
    u64 m_owner;
    u64 m_physical_addr;
    usize m_size;
};

} // namespace acos::ipc
