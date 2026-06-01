#include "textbox.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>

namespace acos::gui {

// Helper functions
static inline usize strlen_impl(const char* s) {
    usize len = 0;
    while (s && s[len]) len++;
    return len;
}

static inline void memcpy_impl(void* dest, const void* src, usize size) {
    u8* d = (u8*)dest;
    const u8* s = (const u8*)src;
    for (usize i = 0; i < size; i++) {
        d[i] = s[i];
    }
}

TextBox::TextBox() 
    : m_cursor(0), m_max_length(512), m_placeholder(nullptr),
      m_text_color(g_current_theme.text), m_bg_color(g_current_theme.widget_bg),
      m_cursor_blink_time(0), m_cursor_visible(true) {
    m_rect.w = 200;
    m_rect.h = 30;
    m_buffer[0] = '\0';
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled | (u32)WidgetFlags::Focusable;
}

TextBox::~TextBox() {}

void TextBox::draw(acos::graphics::Renderer* renderer) {
    if (!(m_flags & (u32)WidgetFlags::Visible)) return;
    
    // Draw background
    renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 2, m_bg_color);
    
    // Draw border
    u32 border_color = (m_state == WidgetState::Focused) ? g_current_theme.accent : g_current_theme.border;
    renderer->draw_border(m_rect.x, m_rect.y, m_rect.w, m_rect.h, border_color, 2);
    
    // Draw text
    if (m_buffer[0] != '\0') {
        renderer->draw_text(m_buffer, m_rect.x + 5, m_rect.y + 6, m_text_color);
    } else if (m_placeholder) {
        renderer->draw_text(m_placeholder, m_rect.x + 5, m_rect.y + 6, 0xFF888888);
    }
    
    // Draw cursor if focused
    if (m_state == WidgetState::Focused && m_cursor_visible) {
        u32 cursor_x = m_rect.x + 5 + (m_cursor * 8);
        renderer->draw_line(cursor_x, m_rect.y + 6, cursor_x, m_rect.y + m_rect.h - 6, m_text_color);
    }
}

void TextBox::handle_event(const acos::input::InputEvent& event) {
    if (!(m_flags & (u32)WidgetFlags::Enabled)) return;
    
    if (event.type == acos::input::InputType::Keyboard) {
        if (m_state != WidgetState::Focused) return;
        
        // Handle keyboard input
        // event.code would contain the key code
        if (event.code >= 32 && event.code < 127) {
            // Printable character
            if (m_cursor < m_max_length - 1) {
                m_buffer[m_cursor++] = (char)event.code;
                m_buffer[m_cursor] = '\0';
            }
        } else if (event.code == 8) {
            // Backspace
            if (m_cursor > 0) {
                m_cursor--;
                m_buffer[m_cursor] = '\0';
            }
        }
    }
}

void TextBox::update(u64 delta_ms) {
    if (m_state == WidgetState::Focused) {
        m_cursor_blink_time += delta_ms;
        if (m_cursor_blink_time > 500) {
            m_cursor_visible = !m_cursor_visible;
            m_cursor_blink_time = 0;
        }
    }
}

void TextBox::set_text(const char* text) {
    if (!text) {
        m_buffer[0] = '\0';
        m_cursor = 0;
        return;
    }
    
    usize len = strlen_impl(text);
    if (len >= m_max_length) len = m_max_length - 1;
    
    memcpy_impl(m_buffer, text, len);
    m_buffer[len] = '\0';
    m_cursor = len;
}

void TextBox::clear() {
    m_buffer[0] = '\0';
    m_cursor = 0;
}

} // namespace acos::gui
