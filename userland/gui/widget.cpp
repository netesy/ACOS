#include "widget.h"
#include "theme.h"

namespace acos::gui {

Widget::Widget() : m_rect{0, 0, 0, 0}, m_parent(nullptr), m_child_count(0), 
                   m_flags((u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled),
                   m_state(WidgetState::Normal), m_elevation(0) {
    for (u32 i = 0; i < 32; i++) m_children[i] = nullptr;
}
Widget::~Widget() {}

void Widget::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Keyboard && event.code == 9) { // Tab key
        bool found_current = false;
        for (u32 i = 0; i < m_child_count; i++) {
            if (m_children[i] && m_children[i]->is_focused()) {
                m_children[i]->set_focused(false);
                found_current = true;
                for (u32 j = (i + 1) % m_child_count; j != i; j = (j + 1) % m_child_count) {
                    if (m_children[j] && (m_children[j]->m_flags & (u32)WidgetFlags::Focusable)) {
                        m_children[j]->set_focused(true);
                        return;
                    }
                }
                break;
            }
        }
        if (!found_current && m_child_count > 0) {
            for (u32 i = 0; i < m_child_count; i++) {
                if (m_children[i] && (m_children[i]->m_flags & (u32)WidgetFlags::Focusable)) {
                    m_children[i]->set_focused(true);
                    return;
                }
            }
        }
    }

    for (u32 i = 0; i < m_child_count; i++) {
        if (m_children[i] && m_children[i]->is_enabled()) {
            m_children[i]->handle_event(event);
        }
    }
}

void Widget::add_child(Widget* child) {
    if (m_child_count < 32 && child) {
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
    if (v) m_flags |= (u32)WidgetFlags::Visible;
    else m_flags &= ~(u32)WidgetFlags::Visible;
}

void Widget::set_enabled(bool e) {
    if (e) m_flags |= (u32)WidgetFlags::Enabled;
    else m_flags &= ~(u32)WidgetFlags::Enabled;
}

void Widget::set_focused(bool f) {
    if (f) m_state = WidgetState::Focused;
    else if (m_state == WidgetState::Focused) m_state = WidgetState::Normal;
}

void Widget::update(u64 delta_ms) {
    for (u32 i = 0; i < m_child_count; i++) {
        if (m_children[i]) m_children[i]->update(delta_ms);
    }
}

void Widget::draw_shadow(acos::graphics::Renderer* renderer) {
    if (m_elevation > 0 && renderer) {
        // Material design inspired shadows: depth increases offset and blur (simulated by larger area/lower alpha)
        u32 offset = m_elevation;
        u8 alpha = (u8)(g_current_theme.shadow_alpha / m_elevation);
        renderer->draw_shadow(m_rect.x, m_rect.y, m_rect.w, m_rect.h, offset, alpha);
    }
}

} // namespace acos::gui
