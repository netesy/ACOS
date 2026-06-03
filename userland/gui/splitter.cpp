#include "splitter.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Splitter::Splitter(Orientation orient) : m_orient(orient), m_first(nullptr), m_second(nullptr), m_ratio(0.5f), m_dragging(false) {}

void Splitter::set_widgets(Widget* first, Widget* second) {
    m_first = first;
    m_second = second;
    if (first) first->set_parent(this);
    if (second) second->set_parent(this);
}

void Splitter::set_split_ratio(float ratio) {
    m_ratio = ratio;
    if (m_ratio < 0.05f) m_ratio = 0.05f;
    if (m_ratio > 0.95f) m_ratio = 0.95f;
}

void Splitter::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    i32 split_pos;
    if (m_orient == Orientation::Horizontal) {
        split_pos = (i32)(m_rect.w * m_ratio);
        if (m_first) {
            m_first->set_position(m_rect.x, m_rect.y);
            m_first->set_size(split_pos - 2, m_rect.h);
            m_first->draw(renderer);
        }
        if (m_second) {
            m_second->set_position(m_rect.x + split_pos + 2, m_rect.y);
            m_second->set_size(m_rect.w - split_pos - 2, m_rect.h);
            m_second->draw(renderer);
        }
        renderer->fill_rect(m_rect.x + split_pos - 2, m_rect.y, 4, m_rect.h, g_current_theme.border);
    } else {
        split_pos = (i32)(m_rect.h * m_ratio);
        if (m_first) {
            m_first->set_position(m_rect.x, m_rect.y);
            m_first->set_size(m_rect.w, split_pos - 2);
            m_first->draw(renderer);
        }
        if (m_second) {
            m_second->set_position(m_rect.x, m_rect.y + split_pos + 2);
            m_second->set_size(m_rect.w, m_rect.h - split_pos - 2);
            m_second->draw(renderer);
        }
        renderer->fill_rect(m_rect.x, m_rect.y + split_pos - 2, m_rect.w, 4, g_current_theme.border);
    }
}

void Splitter::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        i32 split_pos = (m_orient == Orientation::Horizontal) ? (i32)(m_rect.w * m_ratio) : (i32)(m_rect.h * m_ratio);
        Rect handle_rect;
        if (m_orient == Orientation::Horizontal) handle_rect = {m_rect.x + split_pos - 5, m_rect.y, 10, m_rect.h};
        else handle_rect = {m_rect.x, m_rect.y + split_pos - 5, m_rect.w, 10};

        if (pressed && handle_rect.contains(mx, my)) m_dragging = true;
        else if (!pressed) m_dragging = false;

        if (m_dragging) {
            if (m_orient == Orientation::Horizontal) set_split_ratio((float)(mx - m_rect.x) / m_rect.w);
            else set_split_ratio((float)(my - m_rect.y) / m_rect.h);
        }
    }
    if (m_first) m_first->handle_event(event);
    if (m_second) m_second->handle_event(event);
}

} // namespace acos::gui
