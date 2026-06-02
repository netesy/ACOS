#include "scrollbar.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ScrollBar::ScrollBar(Orientation orientation)
    : m_orientation(orientation), m_value(0), m_min(0), m_max(100), m_page_size(10),
      m_dragging(false), m_drag_start(0) {
    if (m_orientation == Orientation::Vertical) {
        m_rect.w = 12;
        m_rect.h = 100;
    } else {
        m_rect.w = 100;
        m_rect.h = 12;
    }
}

ScrollBar::~ScrollBar() {}

void ScrollBar::set_value(i32 v) {
    if (v < m_min) m_value = m_min;
    else if (v > m_max - m_page_size) m_value = m_max - m_page_size;
    else m_value = v;
}

void ScrollBar::set_range(i32 min, i32 max, i32 page_size) {
    m_min = min;
    m_max = max;
    m_page_size = page_size;
    set_value(m_value);
}

void ScrollBar::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    // Track
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.surface, 80);

    // Thumb calculation
    i32 range = m_max - m_min;
    if (range <= m_page_size) return;

    float ratio = (float)m_page_size / range;
    i32 thumb_size, thumb_pos;

    if (m_orientation == Orientation::Vertical) {
        thumb_size = (i32)(m_rect.h * ratio);
        if (thumb_size < 20) thumb_size = 20;
        thumb_pos = (i32)((float)m_value / (range - m_page_size) * (m_rect.h - thumb_size));
        renderer->fill_rounded_rect(m_rect.x + 2, m_rect.y + thumb_pos, m_rect.w - 4, thumb_size, 4, g_current_theme.text_secondary);
    } else {
        thumb_size = (i32)(m_rect.w * ratio);
        if (thumb_size < 20) thumb_size = 20;
        thumb_pos = (i32)((float)m_value / (range - m_page_size) * (m_rect.w - thumb_size));
        renderer->fill_rounded_rect(m_rect.x + thumb_pos, m_rect.y + 2, thumb_size, m_rect.h - 4, 4, g_current_theme.text_secondary);
    }
}

void ScrollBar::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        if (pressed && hit_test(mx, my)) {
            m_dragging = true;
            m_drag_start = (m_orientation == Orientation::Vertical) ? my : mx;
        } else if (!pressed) {
            m_dragging = false;
        }

        if (m_dragging) {
            i32 pos = (m_orientation == Orientation::Vertical) ? my : mx;
            i32 delta = pos - m_drag_start;
            // Simplified drag logic
            set_value(m_value + delta);
            m_drag_start = pos;
        }
    }
}

} // namespace acos::gui
