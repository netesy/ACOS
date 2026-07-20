#pragma once
#include <acos/types.h>

namespace acos {

// 1. Optional
template <typename T>
class Optional {
public:
    Optional() : m_has_value(false) {}
    Optional(const T& value) : m_value(value), m_has_value(true) {}

    bool has_value() const { return m_has_value; }
    const T& value() const { return m_value; }
    T& value() { return m_value; }

    const T* operator->() const { return &m_value; }
    T* operator->() { return &m_value; }

    const T& operator*() const { return m_value; }
    T& operator*() { return m_value; }

    explicit operator bool() const { return m_has_value; }

private:
    T m_value;
    bool m_has_value;
};

// 2. Expected
template <typename T, typename E>
class Expected {
public:
    Expected(const T& val) : m_val(val), m_has_value(true) {}
    Expected(const E& err) : m_err(err), m_has_value(false) {}

    bool has_value() const { return m_has_value; }
    const T& value() const { return m_val; }
    const E& error() const { return m_err; }

    explicit operator bool() const { return m_has_value; }

private:
    T m_val;
    E m_err;
    bool m_has_value;
};

// 3. UniquePtr
template <typename T>
class UniquePtr {
public:
    UniquePtr() : m_ptr(nullptr) {}
    explicit UniquePtr(T* ptr) : m_ptr(ptr) {}
    ~UniquePtr() { reset(); }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            reset();
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    T* get() const { return m_ptr; }
    T* operator->() const { return m_ptr; }
    T& operator*() const { return *m_ptr; }

    explicit operator bool() const { return m_ptr != nullptr; }

    void reset(T* ptr = nullptr) {
        if (m_ptr) {
            m_ptr->~T();
            // Free memory using acos memory rules
        }
        m_ptr = ptr;
    }

private:
    T* m_ptr;
};

// 4. Vector
template <typename T>
class Vector {
public:
    Vector();
    ~Vector();

    void push_back(const T& value);
    void clear();

    usize size() const { return m_size; }
    T& operator[](usize index) { return m_data[index]; }
    const T& operator[](usize index) const { return m_data[index]; }

private:
    T* m_data;
    usize m_size;
    usize m_capacity;
};

// 5. String
class String {
public:
    String();
    String(const char* s);
    String(const String& other);
    ~String();

    const char* c_str() const { return m_data; }
    usize length() const { return m_length; }

private:
    char* m_data;
    usize m_length;
};

// JSON Helper
class JSONValue {
public:
    static JSONValue parse(const char* json_str);
    const char* get_string(const char* key) const;
    int get_int(const char* key) const;
};

// Utilities
void to_hex(char* out, const u8* data, usize len);
void from_hex(u8* out, const char* hex);

} // namespace acos
