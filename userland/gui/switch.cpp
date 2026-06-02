#include "switch.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Switch::Switch(const char* label) : m_label(label), m_on(false) {
    m_rect.w = 40;
    m_rect.h = 20;
}

Switch::~Switch() {}

void Switch::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    u32 track_w = 36;
    u32 track_h = 18;
    i32 tx = m_rect.x;
    i32 ty = m_rect.y + (m_rect.h - track_h) / 2;

    // Track
    u32 track_color = m_on ? g_current_theme.primary : g_current_theme.surface;
    renderer->blend_rect(tx, ty, track_w, track_h, track_color, 180);
    renderer->draw_rounded_rect(tx, ty, track_w, track_h, track_h / 2, g_current_theme.border);

    // Knob
    u32 knob_size = 14;
    i32 knob_x = m_on ? (tx + track_w - knob_size - 2) : (tx + 2);
    i32 knob_y = ty + (track_h - knob_size) / 2;

    renderer->fill_circle(knob_x + knob_size / 2, knob_y + knob_size / 2, knob_size / 2, g_current_theme.text);

    if (m_label) {
        renderer->draw_text(m_label, tx + track_w + 8, m_rect.y + (m_rect.h / 2) - 8, g_current_theme.text);
    }
}

void Switch::handle_event(const acos::input::InputEvent& event) {
    if (!is_enabled()) return;

    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        bool over = hit_test(mx, my);
        if (over) {
            m_state = WidgetState::Hovered;
            if (pressed) {
                m_on = !m_on;
                m_state = WidgetState::Pressed;
            }
        } else {
            m_state = WidgetState::Normal;
        }
    }
}

} // namespace acos::gui
