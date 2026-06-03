#pragma once
#include <acos/types.h>

namespace acos::ui {

class UIContext;

template<typename T>
struct Ref {
    u32 index;
    u32 generation;

    Ref(u32 idx = 0, u32 gen = 0) : index(idx), generation(gen) {}

    template<typename U>
    Ref(const Ref<U>& other) : index(other.index), generation(other.generation) {}

    static Ref null() { return {0, 0}; }
    bool is_null() const { return generation == 0; }

    T* get(UIContext* ctx) const;
};

} // namespace acos::ui
