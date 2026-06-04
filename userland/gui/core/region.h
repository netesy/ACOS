#pragma once
#include <acos/types.h>
#include <acos/runtime.h>
#include "ref.h"

namespace acos::gui {

class Region {
    struct Slot {
        u32 generation;
        bool occupied;
        void (*destructor)(void*);
        alignas(16) u8 storage[512];
    };

public:
    Region(u32 capacity = 1024);
    ~Region();

    template <typename T, typename... Args>
    Ref<T> alloc(Args&&... args) {
        static_assert(sizeof(T) <= sizeof(Slot::storage), "Widget too large for Region slot");
        u32 index = find_free_slot();
        if (index == 0xFFFFFFFF) return Ref<T>();

        Slot& slot = m_slots[index];
        slot.occupied = true;
        slot.generation++;
        slot.destructor = [](void* ptr) {
            static_cast<T*>(ptr)->~T();
        };

        new (slot.storage) T(acos::gui::forward<Args>(args)...);

        return Ref<T>(this, index, slot.generation);
    }

    void dealloc(u32 index, u32 generation);

    void* get_raw(u32 index, u32 generation) {
        if (index >= m_capacity) return nullptr;
        Slot& slot = m_slots[index];
        if (!slot.occupied || slot.generation != generation) return nullptr;
        return slot.storage;
    }

    template <typename T>
    Ref<T> get_ref(T* ptr) {
        uptr addr = reinterpret_cast<uptr>(ptr);
        for (u32 i = 0; i < m_capacity; i++) {
            uptr slot_addr = reinterpret_cast<uptr>(m_slots[i].storage);
            if (addr == slot_addr) {
                if (m_slots[i].occupied) {
                    return Ref<T>(this, i, m_slots[i].generation);
                }
                break;
            }
        }
        return Ref<T>();
    }

private:
    u32 find_free_slot();

    Slot* m_slots;
    u32 m_capacity;
};

// Helper for perfect forwarding
template<typename T> struct RemoveReference { typedef T Type; };
template<typename T> struct RemoveReference<T&> { typedef T Type; };
template<typename T> struct RemoveReference<T&&> { typedef T Type; };

template<typename T>
constexpr T&& forward(typename RemoveReference<T>::Type& t) noexcept {
    return static_cast<T&&>(t);
}

template<typename T>
constexpr T&& forward(typename RemoveReference<T>::Type&& t) noexcept {
    return static_cast<T&&>(t);
}

} // namespace acos::gui
