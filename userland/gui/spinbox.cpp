#include "spinbox.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

SpinBox::SpinBox(i32 min, i32 max)
    : m_value(min), m_min(min), m_max(max), m_up_hovered(false), m_down_hovered(false) {
    m_rect.w = 80;
    m_rect.h = 28;
    m_flags |= (u32)WidgetFlags::Focusable;
}

SpinBox::~SpinBox() {}

void SpinBox::set_value(i32 v) {
    if (v < m_min) v = m_min;
    if (v > m_max) v = m_max;
    if (m_value != v) {
        m_value = v;
        on_value_changed.emit(m_value);
    }
}

void SpinBox::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    // Field background
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w - 24, m_rect.h, g_current_theme.surface, 200);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 4, g_current_theme.border);

    // Value text
    char buf[16];
    // Simple itoa for freestanding
    int val = m_value;
    int i = 0;
    bool neg = false;
    if (val < 0) { neg = true; val = -val; }
    do { buf[i++] = (val % 10) + '0'; val /= 10; } while (val);
    if (neg) buf[i++] = '-';
    for (int j = 0; j < i/2; j++) { char t = buf[j]; buf[j] = buf[i-j-1]; buf[i-j-1] = t; }
    buf[i] = '\0';
    renderer->draw_text(buf, m_rect.x + 8, m_rect.y + 6, g_current_theme.text);

    // Buttons
    u32 btn_x = m_rect.x + m_rect.w - 24;
    u32 up_y = m_rect.y;
    u32 dn_y = m_rect.y + m_rect.h / 2;
    u32 btn_h = m_rect.h / 2;

    renderer->blend_rect(btn_x, up_y, 24, btn_h, m_up_hovered ? g_current_theme.primary : g_current_theme.surface, 150);
    renderer->blend_rect(btn_x, dn_y, 24, btn_h, m_down_hovered ? g_current_theme.primary : g_current_theme.surface, 150);
    renderer->draw_line(btn_x, dn_y, m_rect.x + m_rect.w, dn_y, g_current_theme.border);
    renderer->draw_line(btn_x, up_y, btn_x, m_rect.y + m_rect.h, g_current_theme.border);

    // Arrows
    renderer->draw_text("+", btn_x + 8, up_y + 2, g_current_theme.text);
    renderer->draw_text("-", btn_x + 8, dn_y + 2, g_current_theme.text);
}

void SpinBox::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        m_up_hovered = (mx >= m_rect.x + m_rect.w - 24 && mx < m_rect.x + m_rect.w && my >= m_rect.y && my < m_rect.y + m_rect.h / 2);
        m_down_hovered = (mx >= m_rect.x + m_rect.w - 24 && mx < m_rect.x + m_rect.w && my >= m_rect.y + m_rect.h / 2 && my < m_rect.y + m_rect.h);

        if (pressed) {
            if (m_up_hovered) set_value(m_value + 1);
            if (m_down_hovered) set_value(m_value - 1);
        }
    }
}

} // namespace acos::gui
