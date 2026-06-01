#include "button.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>

namespace acos::gui {

// Helper function for string length
static inline usize strlen_impl(const char* s) {
    usize len = 0;
    while (s && s[len]) len++;
    return len;
}

Button::Button(const char* label) 
    : m_label(label), m_on_click(nullptr), m_mouse_over(false), m_press_time(0) {
    m_rect.w = 100;
    m_rect.h = 40;
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled | (u32)WidgetFlags::Clickable;
    m_state = WidgetState::Normal;
    
    m_bg_color = g_current_theme.widget_bg;
    m_text_color = g_current_theme.text;
    m_hover_color = g_current_theme.accent;
    m_pressed_color = 0xFF0066CC;
}

Button::~Button() {}

void Button::draw(acos::graphics::Renderer* renderer) {
    if (!(m_flags & (u32)WidgetFlags::Visible)) return;
    
    // Draw button background based on state
    u32 bg_color = m_bg_color;
    if (m_state == WidgetState::Pressed) {
        bg_color = m_pressed_color;
    } else if (m_state == WidgetState::Hovered) {
        bg_color = m_hover_color;
    }
    
    // Draw button with rounded corners
    renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 4, bg_color);
    
    // Draw border
    renderer->draw_border(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.border, 1);
    
    // Draw label text centered
    if (m_label) {
        i32 text_x = m_rect.x + (m_rect.w / 2) - (i32)(strlen_impl(m_label) * 4);
        i32 text_y = m_rect.y + (m_rect.h / 2) - 4;
        renderer->draw_text(m_label, (u32)text_x, (u32)text_y, m_text_color);
    }
}

void Button::handle_event(const acos::input::InputEvent& event) {
    if (!(m_flags & (u32)WidgetFlags::Enabled)) return;
    
    if (event.type == acos::input::InputType::Mouse) {
        // Extract mouse position and button state from event
        // Simplified: use code field for button state
        i32 mouse_x = (i32)((event.code >> 16) & 0xFFFF);
        i32 mouse_y = (i32)(event.code & 0xFFFF);
        bool button_pressed = (event.value & 0x01) != 0; // Left mouse button
        
        // Check if mouse is over button using hit test
        bool was_over = m_mouse_over;
        m_mouse_over = (mouse_x >= m_rect.x && mouse_x < m_rect.x + m_rect.w &&
                        mouse_y >= m_rect.y && mouse_y < m_rect.y + m_rect.h);
        
        // Handle state transitions
        if (m_mouse_over && !was_over) {
            // Mouse entered button
            m_state = WidgetState::Hovered;
        } else if (!m_mouse_over && was_over) {
            // Mouse left button
            m_state = WidgetState::Normal;
        }
        
        // Handle click
        if (m_mouse_over && button_pressed) {
            m_state = WidgetState::Pressed;
            m_press_time = 0;
            
            // Invoke click callback
            if (m_on_click) {
                m_on_click(this);
            }
        } else if (!button_pressed && m_state == WidgetState::Pressed) {
            // Button released
            m_state = m_mouse_over ? WidgetState::Hovered : WidgetState::Normal;
        }
    }
}

void Button::update(u64 delta_ms) {
    if (m_state == WidgetState::Pressed) {
        m_press_time += delta_ms;
        if (m_press_time > 100) {
            m_state = m_mouse_over ? WidgetState::Hovered : WidgetState::Normal;
        }
    }
}

} // namespace acos::gui
