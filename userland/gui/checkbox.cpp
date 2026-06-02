#include "checkbox.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

CheckBox::CheckBox(const char* label) : m_label(label), m_checked(false) {
    m_rect.w = 20;
    m_rect.h = 20;
}

CheckBox::~CheckBox() {}

void CheckBox::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    u32 box_size = 18;
    i32 bx = m_rect.x;
    i32 by = m_rect.y + (m_rect.h - box_size) / 2;

    // Checkbox frame
    renderer->blend_rect(bx, by, box_size, box_size, g_current_theme.surface, 150);
    u32 border_color = (m_state == WidgetState::Hovered) ? g_current_theme.primary : g_current_theme.border;
    renderer->draw_rounded_rect(bx, by, box_size, box_size, 4, border_color);

    if (m_checked) {
        // Draw cross or checkmark
        renderer->draw_line(bx + 4, by + 4, bx + box_size - 4, by + box_size - 4, g_current_theme.primary);
        renderer->draw_line(bx + 4, by + box_size - 4, bx + box_size - 4, by + 4, g_current_theme.primary);
    }

    if (m_label) {
        renderer->draw_text(m_label, bx + box_size + 8, m_rect.y + (m_rect.h / 2) - 8, g_current_theme.text);
    }
}

void CheckBox::handle_event(const acos::input::InputEvent& event) {
    if (!is_enabled()) return;

    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        bool over = hit_test(mx, my);
        if (over) {
            m_state = WidgetState::Hovered;
            if (pressed) {
                m_checked = !m_checked;
                m_state = WidgetState::Pressed;
            }
        } else {
            m_state = WidgetState::Normal;
        }
    }
}

} // namespace acos::gui
