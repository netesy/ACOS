#include "radiobutton.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

RadioButton::RadioButton(const char* label)
    : m_label(label), m_selected(false), m_group(nullptr) {
    m_rect.w = 20;
    m_rect.h = 20;
}

RadioButton::~RadioButton() {}

void RadioButton::set_selected(bool selected) {
    if (m_selected == selected) return;
    m_selected = selected;
    if (m_selected && m_group) {
        m_group->select(this);
    }
}

void RadioButton::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    u32 radius = 9;
    i32 cx = m_rect.x + radius;
    i32 cy = m_rect.y + m_rect.h / 2;

    // Outer circle
    renderer->blend_rect(m_rect.x, m_rect.y, radius*2, radius*2, g_current_theme.surface, 150);
    u32 border_color = (m_state == WidgetState::Hovered) ? g_current_theme.primary : g_current_theme.border;
    renderer->draw_circle(cx, cy, radius, border_color);

    if (m_selected) {
        // Inner dot
        renderer->fill_circle(cx, cy, 4, g_current_theme.primary);
    }

    if (m_label) {
        renderer->draw_text(m_label, m_rect.x + radius*2 + 8, m_rect.y + (m_rect.h / 2) - 8, g_current_theme.text);
    }
}

void RadioButton::handle_event(const acos::input::InputEvent& event) {
    if (!is_enabled()) return;

    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        bool over = hit_test(mx, my);
        if (over) {
            m_state = WidgetState::Hovered;
            if (pressed) {
                set_selected(true);
                m_state = WidgetState::Pressed;
            }
        } else {
            m_state = WidgetState::Normal;
        }
    }
}

RadioButtonGroup::RadioButtonGroup() : m_count(0) {}

void RadioButtonGroup::add_button(RadioButton* button) {
    if (m_count < 16) {
        m_buttons[m_count++] = button;
        button->set_group(this);
    }
}

void RadioButtonGroup::select(RadioButton* selected_button) {
    for (u32 i = 0; i < m_count; i++) {
        if (m_buttons[i] != selected_button) {
            m_buttons[i]->set_selected(false);
        }
    }
}

} // namespace acos::gui
