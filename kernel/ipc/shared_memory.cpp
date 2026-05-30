#include <kernel/ipc/shared_memory.h>

namespace acos::ipc {

static u64 g_next_region_id = 1;

SharedRegion::SharedRegion(u64 physical_addr, usize size)
    : m_physical_addr(physical_addr), m_size(size) {
    m_id = g_next_region_id++;
}

} // namespace acos::ipc
