#include <acos/utility.h>
#include <acos/process.h>
#include <acos/runtime.h>

namespace acos {

// Vector implementation
template <typename T>
Vector<T>::Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

template <typename T>
Vector<T>::~Vector() {
    clear();
    if (m_data) {
        memory::free(m_data);
    }
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (m_size >= m_capacity) {
        usize new_cap = m_capacity == 0 ? 4 : m_capacity * 2;
        T* new_data = static_cast<T*>(memory::malloc(new_cap * sizeof(T)));
        if (!new_data) return;

        for (usize i = 0; i < m_size; i++) {
            new_data[i] = m_data[i];
        }

        if (m_data) memory::free(m_data);
        m_data = new_data;
        m_capacity = new_cap;
    }
    m_data[m_size++] = value;
}

template <typename T>
void Vector<T>::clear() {
    m_size = 0;
}

// Instantiate commonly used Vector types
template class Vector<int>;
template class Vector<u32>;
template class Vector<u64>;

// String implementation
String::String() : m_data(nullptr), m_length(0) {
    m_data = static_cast<char*>(memory::malloc(1));
    m_data[0] = '\0';
}

String::String(const char* s) {
    if (!s) {
        m_data = static_cast<char*>(memory::malloc(1));
        m_data[0] = '\0';
        m_length = 0;
        return;
    }
    m_length = strlen(s);
    m_data = static_cast<char*>(memory::malloc(m_length + 1));
    memcpy(m_data, s, m_length);
    m_data[m_length] = '\0';
}

String::String(const String& other) {
    m_length = other.m_length;
    m_data = static_cast<char*>(memory::malloc(m_length + 1));
    memcpy(m_data, other.m_data, m_length);
    m_data[m_length] = '\0';
}

String::~String() {
    if (m_data) {
        memory::free(m_data);
    }
}

// JSON Parser stub
JSONValue JSONValue::parse(const char* json_str [[maybe_unused]]) {
    return JSONValue();
}

const char* JSONValue::get_string(const char* key [[maybe_unused]]) const {
    return nullptr;
}

int JSONValue::get_int(const char* key [[maybe_unused]]) const {
    return 0;
}

// Hex helpers
void to_hex(char* out, const u8* data, usize len) {
    const char hex_chars[] = "0123456789ABCDEF";
    for (usize i = 0; i < len; i++) {
        out[i * 2] = hex_chars[(data[i] >> 4) & 0x0F];
        out[i * 2 + 1] = hex_chars[data[i] & 0x0F];
    }
    out[len * 2] = '\0';
}

void from_hex(u8* out, const char* hex) {
    auto parse_nibble = [](char c) -> u8 {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        return 0;
    };

    usize i = 0;
    while (hex[i] && hex[i+1]) {
        out[i / 2] = (parse_nibble(hex[i]) << 4) | parse_nibble(hex[i+1]);
        i += 2;
    }
}

} // namespace acos
