#include "button.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>

namespace acos::gui {

static inline usize strlen_impl(const char* s) {
    usize len = 0;
    while (s && s[len]) len++;
    return len;
}

Button::Button(const char* label) 
    : m_label(label), m_mouse_over(false), m_press_time(0) {
    m_rect.w = 100;
    m_rect.h = 32;
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled | (u32)WidgetFlags::Clickable;
    m_state = WidgetState::Normal;
    m_elevation = 2;
    
    m_bg_color = g_current_theme.surface;
    m_text_color = g_current_theme.text;
    m_hover_color = g_current_theme.primary;
    m_pressed_color = g_current_theme.secondary;
}

Button::~Button() {}

void Button::draw(acos::graphics::Renderer* renderer) {
    if (!(m_flags & (u32)WidgetFlags::Visible)) return;
    
    draw_shadow(renderer);

    u32 bg_color = m_bg_color;
    u8 alpha = 200;

    if (m_state == WidgetState::Pressed) {
        bg_color = m_pressed_color;
        alpha = 255;
    } else if (m_state == WidgetState::Hovered) {
        bg_color = m_hover_color;
        alpha = 220;
    }
    
    renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.widget_radius, (bg_color & 0x00FFFFFF) | ((u32)alpha << 24));
    
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.widget_radius, g_current_theme.border);
    
    if (m_label) {
        u32 char_w = 8;
        u32 char_h = 16;
        if (acos::graphics::Font::get_default()) {
            char_w = acos::graphics::Font::get_default()->width();
            char_h = acos::graphics::Font::get_default()->height();
        }

        i32 text_x = m_rect.x + (m_rect.w / 2) - (i32)(strlen_impl(m_label) * char_w / 2);
        i32 text_y = m_rect.y + (m_rect.h / 2) - (i32)(char_h / 2);
        renderer->draw_text(m_label, (u32)text_x, (u32)text_y, m_text_color);
    }
}

void Button::handle_event(const acos::input::InputEvent& event) {
    if (!(m_flags & (u32)WidgetFlags::Enabled)) return;
    
    if (event.type == acos::input::InputType::Mouse) {
        i32 mouse_x = (i32)((event.code >> 16) & 0xFFFF);
        i32 mouse_y = (i32)(event.code & 0xFFFF);
        bool button_pressed = (event.value & 0x01) != 0;
        
        bool was_over = m_mouse_over;
        m_mouse_over = hit_test(mouse_x, mouse_y);
        
        if (m_mouse_over && !was_over) {
            m_state = WidgetState::Hovered;
            m_elevation = 4;
        } else if (!m_mouse_over && was_over) {
            m_state = WidgetState::Normal;
            m_elevation = 2;
        }
        
        if (m_mouse_over && button_pressed) {
            m_state = WidgetState::Pressed;
            m_elevation = 1;
            m_press_time = 0;
            m_on_click_signal.emit();
        } else if (!button_pressed && m_state == WidgetState::Pressed) {
            m_state = m_mouse_over ? WidgetState::Hovered : WidgetState::Normal;
            m_elevation = m_mouse_over ? 4 : 2;
        }
    }
}

void Button::update(u64 delta_ms) {
    if (m_state == WidgetState::Pressed) {
        m_press_time += delta_ms;
        if (m_press_time > 100) {
            m_state = m_mouse_over ? WidgetState::Hovered : WidgetState::Normal;
            m_elevation = m_mouse_over ? 4 : 2;
        }
    }
}

} // namespace acos::gui
