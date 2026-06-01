#include "widget.h"

namespace acos::gui {

Widget::Widget() : m_rect{0, 0, 0, 0}, m_parent(nullptr), m_child_count(0), 
                   m_flags((u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled),
                   m_state(WidgetState::Normal) {}
Widget::~Widget() {}

void Widget::handle_event(const acos::input::InputEvent& event) {
    (void)event;
}

void Widget::add_child(Widget* child) {
    if (m_child_count < 16 && child) {
        m_children[m_child_count++] = child;
        child->set_parent(this);
    }
}

void Widget::remove_child(Widget* child) {
    for (u32 i = 0; i < m_child_count; i++) {
        if (m_children[i] == child) {
            for (u32 j = i; j < m_child_count - 1; j++) {
                m_children[j] = m_children[j + 1];
            }
            m_child_count--;
            break;
        }
    }
}

void Widget::set_visible(bool v) {
    if (v) {
        m_flags |= (u32)WidgetFlags::Visible;
    } else {
        m_flags &= ~(u32)WidgetFlags::Visible;
    }
}

void Widget::set_enabled(bool e) {
    if (e) {
        m_flags |= (u32)WidgetFlags::Enabled;
    } else {
        m_flags &= ~(u32)WidgetFlags::Enabled;
    }
}

void Widget::set_focused(bool f) {
    if (f) {
        m_state = WidgetState::Focused;
    } else if (m_state == WidgetState::Focused) {
        m_state = WidgetState::Normal;
    }
}

void Widget::update(u64 delta_ms [[maybe_unused]]) {
    // Default implementation does nothing
}

} // namespace acos::gui
