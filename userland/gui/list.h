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
        node->value = value; node->next = nullptr;
        if (!m_head) { m_head = node; m_tail = node; }
        else { m_tail->next = node; m_tail = node; }
        m_count++;
    }
    u32 count() const { return m_count; }
    Node* head() const { return m_head; }
private:
    Node* m_head; Node* m_tail; u32 m_count;
};

} // namespace acos::ui
