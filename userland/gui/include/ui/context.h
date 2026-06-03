#pragma once
#include <ui/region.h>
#include <ui/pool.h>
#include <ui/ref.h>

namespace acos::ui {

class Widget;

class UIContext {
public:
    UIContext(usize region_size = 1024 * 1024, usize pool_size = 4096)
        : m_region(region_size), m_pool(pool_size) {}

    template<typename T, typename... Args>
    Ref<T> make(Args&&... args) {
        T* ptr = m_region.make<T>(forward<Args>(args)...);
        if (!ptr) return Ref<T>::null();
        u32 index = m_pool.store(ptr);
        return { index, m_pool.generation(index) };
    }

    ObjectPool& pool() { return m_pool; }
    Region& region() { return m_region; }

private:
    Region m_region;
    ObjectPool m_pool;

    template<typename T>
    struct identity { using type = T; };

    template<typename T>
    static T&& forward(typename identity<T>::type& t) { return static_cast<T&&>(t); }

    template<typename T>
    static T&& forward(typename identity<T>::type&& t) { return static_cast<T&&>(t); }
};

template<typename T>
T* Ref<T>::get(UIContext* ctx) const {
    return static_cast<T*>(ctx->pool().resolve(index, generation));
}

} // namespace acos::ui
