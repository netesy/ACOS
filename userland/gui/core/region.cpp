#include "region.h"
#include <acos/runtime.h>

namespace acos::gui {

Region::Region(u32 capacity) : m_capacity(capacity) {
    m_slots = new Slot[capacity];
    for (u32 i = 0; i < capacity; i++) {
        m_slots[i].generation = 0;
        m_slots[i].occupied = false;
        m_slots[i].destructor = nullptr;
    }
}

Region::~Region() {
    for (u32 i = 0; i < m_capacity; i++) {
        if (m_slots[i].occupied && m_slots[i].destructor) {
            m_slots[i].destructor(m_slots[i].storage);
        }
    }
    delete[] m_slots;
}

u32 Region::find_free_slot() {
    for (u32 i = 0; i < m_capacity; i++) {
        if (!m_slots[i].occupied) return i;
    }
    return 0xFFFFFFFF;
}

void Region::dealloc(u32 index, u32 generation) {
    if (index >= m_capacity) return;
    Slot& slot = m_slots[index];
    if (slot.occupied && slot.generation == generation) {
        if (slot.destructor) slot.destructor(slot.storage);
        slot.occupied = false;
    }
}

} // namespace acos::gui
