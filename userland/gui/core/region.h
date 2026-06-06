#pragma once
#include <acos/types.h>
#include <acos/runtime.h>
#include "ref.h"

namespace acos::gui {

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

class Region {
    struct Slot {
        ::acos::u32 generation;
        bool occupied;
        void (*destructor)(void*);
        alignas(16) ::acos::u8 storage[4096];
    };

public:
    Region(::acos::u32 capacity = 1024);
    ~Region();

    template <typename T, typename... Args>
    Ref<T> alloc(Args&&... args) {
        static_assert(sizeof(T) <= sizeof(Slot::storage), "Widget too large for Region slot");
        ::acos::u32 index = find_free_slot();
        if (index == 0xFFFFFFFF) return Ref<T>();

        Slot& slot = m_slots[index];
        slot.occupied = true;
        slot.generation++;
        slot.destructor = [](void* ptr) {
            static_cast<T*>(ptr)->~T();
        };

        new (slot.storage) T(forward<Args>(args)...);

        return Ref<T>(this, index, slot.generation);
    }

    void dealloc(::acos::u32 index, ::acos::u32 generation);

    void* get_raw(::acos::u32 index, ::acos::u32 generation) {
        if (index >= m_capacity) return nullptr;
        Slot& slot = m_slots[index];
        if (!slot.occupied || slot.generation != generation) return nullptr;
        return slot.storage;
    }

    template <typename T>
    Ref<T> get_ref(T* ptr) {
        ::acos::uptr addr = reinterpret_cast<::acos::uptr>(ptr);
        ::acos::uptr base_addr = reinterpret_cast<::acos::uptr>(m_slots);

        if (addr < base_addr || addr >= base_addr + (m_capacity * sizeof(Slot))) {
            return Ref<T>();
        }

        ::acos::u32 index = (::acos::u32)((addr - base_addr) / sizeof(Slot));

        if (addr != reinterpret_cast<::acos::uptr>(m_slots[index].storage)) {
            return Ref<T>();
        }

        if (m_slots[index].occupied) {
            return Ref<T>(this, index, m_slots[index].generation);
        }

        return Ref<T>();
    }

private:
    ::acos::u32 find_free_slot();

    Slot* m_slots;
    ::acos::u32 m_capacity;
};

} // namespace acos::gui
