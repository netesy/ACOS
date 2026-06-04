#pragma once
#include <acos/types.h>

namespace acos::gui {

class Region;

void* RefBaseResolve(Region* region, u32 index, u32 generation);

template <typename T>
class Ref {
public:
    Ref() : m_region(nullptr), m_index(0), m_generation(0) {}
    Ref(Region* region, u32 index, u32 generation)
        : m_region(region), m_index(index), m_generation(generation) {}

    T* operator->() const {
        return static_cast<T*>(resolve());
    }

    T& operator*() const {
        return *static_cast<T*>(resolve());
    }

    bool is_valid() const {
        return resolve() != nullptr;
    }

    operator bool() const { return is_valid(); }

    bool operator==(const Ref& other) const {
        return m_region == other.m_region && m_index == other.m_index && m_generation == other.m_generation;
    }

    u32 index() const { return m_index; }
    u32 generation() const { return m_generation; }
    Region* region() const { return m_region; }

    template <typename U>
    Ref<U> static_cast_to() const {
        return Ref<U>(m_region, m_index, m_generation);
    }

private:
    void* resolve() const {
        return RefBaseResolve(m_region, m_index, m_generation);
    }

    Region* m_region;
    u32 m_index;
    u32 m_generation;
};

} // namespace acos::gui
