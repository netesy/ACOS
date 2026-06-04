#pragma once
#include <acos/types.h>
#include "region.h"

namespace acos::ui {

template<typename T>
class List {
public:
    struct Node { T value; Node* next; };
    List() : m_head(nullptr), m_tail(nullptr), m_count(0) {}
    void add(Region& region, const T& value) {
        Node* node = region.make<Node>();
        if (!node) return;
        node->value = value; node->next = nullptr;
        if (!m_head) { m_head = node; m_tail = node; }
        else { m_tail->next = node; m_tail = node; }
        m_count++;
    }
    u32 count() const { return m_count; }
    Node* head() const { return m_head; }

    struct Iterator {
        Node* current;
        bool operator!=(const Iterator& other) const { return current != other.current; }
        void operator++() { current = current->next; }
        T& operator*() { return current->value; }
    };
    Iterator begin() const { return { m_head }; }
    Iterator end() const { return { nullptr }; }

private:
    Node* m_head; Node* m_tail; u32 m_count;
};

} // namespace acos::ui
