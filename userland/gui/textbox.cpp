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

Ref<RenderObject> TextBox::create_render_object() {
    Ref<RenderObject> ro = UIContext::get().region().alloc<RenderTextBox>();
    update_render_object(ro);
    return ro;
}

void TextBox::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    if (render_object) {
        RenderTextBox* rtb = static_cast<RenderTextBox*>(render_object.operator->());
        rtb->set_text(m_buffer);
        rtb->set_placeholder(m_placeholder);
        rtb->set_cursor(m_cursor, m_state == WidgetState::Focused && m_cursor_visible);
    }
}

void TextBox::on_event(Event& event) {
    if (!(m_flags & (u32)WidgetFlags::Enabled)) return;
    
    if (event.raw.type == acos::input::InputType::Keyboard) {
        if (m_state != WidgetState::Focused) return;
        
        u32 code = event.raw.code;
        if (code >= 32 && code < 127) {
            if (m_cursor < m_max_length - 1) {
                m_buffer[m_cursor++] = (char)code;
                m_buffer[m_cursor] = '\0';
                set_paint_dirty();
            }
        } else if (code == 8) { // Backspace
            if (m_cursor > 0) {
                m_cursor--;
                m_buffer[m_cursor] = '\0';
                set_paint_dirty();
            }
        }
        event.stop_propagation();
    } else if (event.raw.type == acos::input::InputType::Mouse) {
        bool pressed = (event.raw.value & 0x01) != 0;
        if (pressed && event.phase == EventPhase::Target) {
            UIContext::get().focus_manager().set_focus(self());
            event.stop_propagation();
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
