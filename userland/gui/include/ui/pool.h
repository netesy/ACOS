#pragma once
#include <acos/types.h>

namespace acos::ui {

struct ObjectEntry {
    void* ptr;
    u32 generation;
};

class ObjectPool {
public:
    ObjectPool(usize capacity) : m_capacity(capacity) {
        m_entries = static_cast<ObjectEntry*>(::operator new(sizeof(ObjectEntry) * capacity));
        for (u32 i = 0; i < capacity; i++) {
            m_entries[i] = { nullptr, 1 };
        }
        m_next_index = 1; // 0 reserved for null
    }

    ~ObjectPool() {
        ::operator delete(m_entries);
    }

    u32 store(void* ptr) {
        if (m_next_index >= m_capacity) return 0;
        u32 index = m_next_index++;
        m_entries[index].ptr = ptr;
        return index;
    }

    u32 generation(u32 index) const {
        if (index >= m_capacity) return 0;
        return m_entries[index].generation;
    }

    void* resolve(u32 index, u32 generation) const {
        if (index >= m_capacity || m_entries[index].generation != generation) return nullptr;
        return m_entries[index].ptr;
    }

    void invalidate(u32 index) {
        if (index < m_capacity) {
            m_entries[index].generation++;
            m_entries[index].ptr = nullptr;
        }
    }

private:
    ObjectEntry* m_entries;
    u32 m_next_index;
    u32 m_capacity;
};

} // namespace acos::ui
