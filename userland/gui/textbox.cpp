#include "textbox.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>

namespace acos::gui {

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
      m_text_color(g_current_theme.text), m_bg_color(g_current_theme.surface),
      m_cursor_blink_time(0), m_cursor_visible(true) {
    m_rect.w = 200;
    m_rect.h = 32;
    m_buffer[0] = '\0';
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled | (u32)WidgetFlags::Focusable;
}

TextBox::~TextBox() {}

void TextBox::draw(acos::graphics::Renderer* renderer) {
    if (!(m_flags & (u32)WidgetFlags::Visible)) return;
    
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_bg_color, 180);
    
    u32 border_color = (m_state == WidgetState::Focused) ? g_current_theme.primary : g_current_theme.border;
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.widget_radius, border_color);
    
    u32 char_w = 8;
    if (acos::graphics::Font::get_default()) char_w = acos::graphics::Font::get_default()->width();

    if (m_buffer[0] != '\0') {
        renderer->draw_text(m_buffer, m_rect.x + 8, m_rect.y + 8, m_text_color);
    } else if (m_placeholder) {
        renderer->draw_text(m_placeholder, m_rect.x + 8, m_rect.y + 8, g_current_theme.text_secondary);
    }
    
    if (m_state == WidgetState::Focused && m_cursor_visible) {
        u32 cursor_x = m_rect.x + 8 + (m_cursor * char_w);
        renderer->draw_line(cursor_x, m_rect.y + 6, cursor_x, m_rect.y + m_rect.h - 6, g_current_theme.primary);
    }
}

void TextBox::handle_event(const acos::input::InputEvent& event) {
    if (!(m_flags & (u32)WidgetFlags::Enabled)) return;
    
    if (event.type == acos::input::InputType::Keyboard) {
        if (m_state != WidgetState::Focused) return;
        
        if (event.code >= 32 && event.code < 127) {
            if (m_cursor < m_max_length - 1) {
                m_buffer[m_cursor++] = (char)event.code;
                m_buffer[m_cursor] = '\0';
            }
        } else if (event.code == 8) {
            if (m_cursor > 0) {
                m_cursor--;
                m_buffer[m_cursor] = '\0';
            }
        }
    } else if (event.type == acos::input::InputType::Mouse) {
        i32 mouse_x = (i32)((event.code >> 16) & 0xFFFF);
        i32 mouse_y = (i32)(event.code & 0xFFFF);
        bool button_pressed = (event.value & 0x01) != 0;
        if (button_pressed) {
            if (hit_test(mouse_x, mouse_y)) m_state = WidgetState::Focused;
            else m_state = WidgetState::Normal;
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
