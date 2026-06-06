#include "region.h"
#include <kernel/memory/heap.h>

namespace acos::gui {

Region::Region(::acos::u32 capacity) : m_capacity(capacity) {
    m_slots = static_cast<Slot*>(::acos::memory::kmalloc(sizeof(Slot) * capacity));
    for (::acos::u32 i = 0; i < capacity; i++) {
        m_slots[i].generation = 0;
        m_slots[i].occupied = false;
        m_slots[i].destructor = nullptr;
    }
}

Region::~Region() {
    for (::acos::u32 i = 0; i < m_capacity; i++) {
        if (m_slots[i].occupied && m_slots[i].destructor) {
            m_slots[i].destructor(m_slots[i].storage);
        }
    }
    ::acos::memory::kfree(m_slots);
}

::acos::u32 Region::find_free_slot() {
    for (::acos::u32 i = 0; i < m_capacity; i++) {
        if (!m_slots[i].occupied) return i;
    }
    return 0xFFFFFFFF;
}

void Region::dealloc(::acos::u32 index, ::acos::u32 generation) {
    if (index >= m_capacity) return;
    Slot& slot = m_slots[index];
    if (slot.occupied && slot.generation == generation) {
        if (slot.destructor) slot.destructor(slot.storage);
        slot.occupied = false;
    }
}

} // namespace acos::gui
