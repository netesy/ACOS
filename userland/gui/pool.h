#pragma once
#include <acos/types.h>
#include <acos/runtime.h>

namespace acos::ui {

class ObjectPool {
public:
    ObjectPool(usize capacity) : m_next_index(1), m_capacity(capacity) {
        m_entries = (Entry*)::operator new(sizeof(Entry) * capacity);
        for (u32 i = 0; i < capacity; i++) m_entries[i] = {nullptr, 1};
    }
    ~ObjectPool() { ::operator delete(m_entries); }

    u32 store(void* ptr) {
        if (m_next_index >= m_capacity) return 0;
        u32 idx = m_next_index++;
        m_entries[idx].ptr = ptr;
        return idx;
    }

    u32 generation(u32 index) const { return index < m_capacity ? m_entries[index].generation : 0; }

    void* resolve(u32 index, u32 generation) const {
        if (index >= m_capacity || m_entries[index].generation != generation) return nullptr;
        return m_entries[index].ptr;
    }

private:
    struct Entry {
        void* ptr;
        u32 generation;
    } *m_entries;
    u32 m_next_index;
    u32 m_capacity;
};

} // namespace acos::ui
