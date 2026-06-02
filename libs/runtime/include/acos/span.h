#pragma once
#include <acos/types.h>

namespace acos {

template <typename T>
class Span {
public:
    constexpr Span() : m_ptr(nullptr), m_size(0) {}
    constexpr Span(T* ptr, usize size) : m_ptr(ptr), m_size(size) {}

    constexpr T* data() const { return m_ptr; }
    constexpr usize size() const { return m_size; }

    constexpr T& operator[](usize index) const { return m_ptr[index]; }

    constexpr T* begin() const { return m_ptr; }
    constexpr T* end() const { return m_ptr + m_size; }

private:
    T* m_ptr;
    usize m_size;
};

} // namespace acos
