#include "slider.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Slider::Slider() : m_value(0.0f), m_min(0.0f), m_max(100.0f), m_dragging(false) {
    m_rect.w = 200;
    m_rect.h = 24;
}

Slider::~Slider() {}

void Slider::set_value(float v) {
    if (v < m_min) m_value = m_min;
    else if (v > m_max) m_value = m_max;
    else m_value = v;
}

void Slider::set_range(float min, float max) {
    m_min = min;
    m_max = max;
    set_value(m_value);
}

void Slider::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    i32 track_h = 4;
    i32 track_y = m_rect.y + (m_rect.h - track_h) / 2;

    // Track
    renderer->blend_rect(m_rect.x, track_y, m_rect.w, track_h, g_current_theme.surface, 150);
    renderer->draw_rounded_rect(m_rect.x, track_y, m_rect.w, track_h, track_h / 2, g_current_theme.border);

    // Active part of track
    float ratio = (m_value - m_min) / (m_max - m_min);
    u32 active_w = static_cast<u32>(m_rect.w * ratio);
    if (active_w > 0) {
        renderer->fill_rect(m_rect.x, track_y, active_w, track_h, g_current_theme.primary);
    }

    // Knob
    u32 knob_size = 14;
    i32 knob_x = m_rect.x + (i32)(m_rect.w * ratio) - knob_size / 2;
    i32 knob_y = m_rect.y + (m_rect.h - knob_size) / 2;

    renderer->fill_circle(knob_x + knob_size / 2, knob_y + knob_size / 2, knob_size / 2, g_current_theme.text);
    u32 knob_border = (m_dragging || m_state == WidgetState::Hovered) ? g_current_theme.primary : g_current_theme.border;
    renderer->draw_circle(knob_x + knob_size / 2, knob_y + knob_size / 2, knob_size / 2, knob_border);
}

void Slider::handle_event(const acos::input::InputEvent& event) {
    if (!is_enabled()) return;

    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        bool over = hit_test(mx, my);
        if (over) m_state = WidgetState::Hovered;
        else m_state = WidgetState::Normal;

        if (pressed && over) {
            m_dragging = true;
        } else if (!pressed) {
            m_dragging = false;
        }

        if (m_dragging) {
            float ratio = (float)(mx - m_rect.x) / m_rect.w;
            if (ratio < 0.0f) ratio = 0.0f;
            if (ratio > 1.0f) ratio = 1.0f;
            set_value(m_min + ratio * (m_max - m_min));
        }
    }
}

} // namespace acos::gui
