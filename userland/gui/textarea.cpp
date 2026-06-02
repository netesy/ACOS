#include "textarea.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>

namespace acos::gui {

static inline usize strlen_impl(const char* s) {
    usize len = 0;
    while (s && s[len]) len++;
    return len;
}

TextArea::TextArea() : m_cursor_pos(0), m_cursor_blink_time(0), m_cursor_visible(true) {
    m_rect.w = 300;
    m_rect.h = 200;
    m_buffer[0] = '\0';
    m_flags |= (u32)WidgetFlags::Focusable;
}

TextArea::~TextArea() {}

void TextArea::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.surface, 180);
    u32 border_color = (m_state == WidgetState::Focused) ? g_current_theme.primary : g_current_theme.border;
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 4, border_color);

    renderer->draw_text(m_buffer, (u32)m_rect.x + 8, (u32)m_rect.y + 8, g_current_theme.text);

    if (m_state == WidgetState::Focused && m_cursor_visible) {
    }
}

void TextArea::handle_event(const acos::input::InputEvent& event) {
    if (!is_enabled()) return;

    if (event.type == acos::input::InputType::Keyboard) {
        if (m_state != WidgetState::Focused) return;
        if (event.code >= 32 && event.code < 127) insert_char((char)event.code);
        else if (event.code == 8) backspace();
        else if (event.code == 13 || event.code == 10) insert_char('\n');
    } else if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;
        if (pressed) {
            if (hit_test(mx, my)) m_state = WidgetState::Focused;
            else m_state = WidgetState::Normal;
        }
    }
}

void TextArea::update(u64 delta_ms) {
    if (m_state == WidgetState::Focused) {
        m_cursor_blink_time += delta_ms;
        if (m_cursor_blink_time > 500) {
            m_cursor_visible = !m_cursor_visible;
            m_cursor_blink_time = 0;
        }
    }
}

void TextArea::insert_char(char c) {
    if (m_cursor_pos < 4095) {
        m_buffer[m_cursor_pos++] = c;
        m_buffer[m_cursor_pos] = '\0';
    }
}

void TextArea::backspace() {
    if (m_cursor_pos > 0) {
        m_cursor_pos--;
        m_buffer[m_cursor_pos] = '\0';
    }
}

void TextArea::set_text(const char* text) {
    if (!text) { m_buffer[0] = '\0'; m_cursor_pos = 0; return; }
    usize len = strlen_impl(text);
    if (len > 4095) len = 4095;
    for (usize i = 0; i < len; i++) m_buffer[i] = text[i];
    m_buffer[len] = '\0';
    m_cursor_pos = (u32)len;
}

} // namespace acos::gui
