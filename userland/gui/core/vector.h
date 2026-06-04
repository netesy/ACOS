#pragma once
#include <acos/types.h>
#include <acos/runtime.h>

namespace acos {

template <typename T>
class Vector {
public:
    Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}
    ~Vector() {
        for (u32 i = 0; i < m_size; i++) {
            m_data[i].~T();
        }
        operator delete[](m_data);
    }

    Vector(const Vector& other) : m_data(nullptr), m_size(0), m_capacity(0) {
        reserve(other.m_capacity);
        for (u32 i = 0; i < other.m_size; i++) {
            m_data[i] = other.m_data[i];
        }
        m_size = other.m_size;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] m_data;
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
            reserve(other.m_capacity);
            for (u32 i = 0; i < other.m_size; i++) {
                m_data[i] = other.m_data[i];
            }
            m_size = other.m_size;
        }
        return *this;
    }

    void push_back(const T& value) {
        if (m_size >= m_capacity) {
            u32 new_capacity = m_capacity == 0 ? 8 : m_capacity * 2;
            reserve(new_capacity);
        }
        m_data[m_size++] = value;
    }

    void reserve(u32 new_capacity) {
        if (new_capacity <= m_capacity) return;
        T* new_data = static_cast<T*>(operator new[](new_capacity * sizeof(T)));
        for (u32 i = 0; i < m_size; i++) {
            new (&new_data[i]) T(m_data[i]);
            m_data[i].~T();
        }
        operator delete[](m_data);
        m_data = new_data;
        m_capacity = new_capacity;
    }

    void remove_at(u32 index) {
        if (index >= m_size) return;
        m_data[index].~T();
        for (u32 i = index; i < m_size - 1; i++) {
            new (&m_data[i]) T(m_data[i + 1]);
            m_data[i + 1].~T();
        }
        m_size--;
    }

    u32 size() const { return m_size; }
    void clear() { m_size = 0; }
    T& operator[](u32 index) { return m_data[index]; }
    const T& operator[](u32 index) const { return m_data[index]; }

    T* begin() { return m_data; }
    T* end() { return m_data + m_size; }
    const T* begin() const { return m_data; }
    const T* end() const { return m_data + m_size; }

private:
    T* m_data;
    u32 m_size;
    u32 m_capacity;
};

} // namespace acos
