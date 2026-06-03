#pragma once
#include <acos/types.h>
#include <acos/runtime.h>

namespace acos::ui {

class Region {
public:
    Region(usize capacity) : m_capacity(capacity) {
        // In a real OS, we would use mmap or a custom heap allocator
        // For now, we assume we can allocate a block
        m_base = static_cast<u8*>(::operator new(capacity));
        m_offset = 0;
    }

    ~Region() {
        ::operator delete(m_base);
    }

    void* allocate(usize size, usize alignment = 8) {
        usize padding = (alignment - (reinterpret_cast<uptr>(m_base + m_offset) % alignment)) % alignment;
        if (m_offset + padding + size > m_capacity) return nullptr;

        m_offset += padding;
        void* ptr = m_base + m_offset;
        m_offset += size;
        return ptr;
    }

    void reset() {
        m_offset = 0;
    }

    template<typename T, typename... Args>
    T* make(Args&&... args) {
        void* ptr = allocate(sizeof(T), alignof(T));
        if (!ptr) return nullptr;
        return new (ptr) T(forward<Args>(args)...);
    }

private:
    u8* m_base;
    usize m_offset;
    usize m_capacity;

    template<typename T>
    struct identity { using type = T; };

    template<typename T>
    static T&& forward(typename identity<T>::type& t) { return static_cast<T&&>(t); }

    template<typename T>
    static T&& forward(typename identity<T>::type&& t) { return static_cast<T&&>(t); }
};

} // namespace acos::ui
