#include "textarea.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>

namespace acos::gui::widgets {

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

Ref<RenderObject> TextArea::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> TextArea::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
