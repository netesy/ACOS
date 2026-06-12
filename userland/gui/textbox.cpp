#include <acos/process.h>
#include <acos/runtime.h>
#include "textbox.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"
#include "core/event_dispatcher.h"
#include <acos/runtime.h>

namespace acos::gui::widgets {

TextBox::TextBox() : m_cursor(0), m_max_length(511), m_placeholder(nullptr),
                   m_text_color(0xFFFFFFFF), m_bg_color(0x33FFFFFF),
                   m_cursor_blink_time(0), m_cursor_visible(false) {
    m_rect = {0, 0, 200, 32};
    m_buffer[0] = '\0';
}

TextBox::~TextBox() {}

Ref<RenderObject> TextBox::create_render_object() {
    return UIContext::get().region().alloc<RenderTextBox>();
}

void TextBox::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rt = static_cast<RenderTextBox*>(render_object.operator->());
    if (rt) {
        rt->set_text(m_buffer);
        rt->set_placeholder(m_placeholder);
        rt->set_cursor((u32)m_cursor, m_cursor_visible && (m_state == WidgetState::Focused));
    }
}

void TextBox::on_event(Event& event) {
    const auto& raw = event.raw;
    if (raw.type == acos::input::InputType::Mouse) {
        if (raw.value & 0x01) { // Left click
            UIContext::get().focus_manager().set_focus(self());
        }
    } else if (raw.type == acos::input::InputType::Keyboard && m_state == WidgetState::Focused) {
        if (raw.code == 8) { // Backspace
            if (m_cursor > 0) {
                m_cursor--;
                m_buffer[m_cursor] = '\0';
                set_paint_dirty();
            }
        } else if (raw.code >= 32 && raw.code <= 126) {
            if (m_cursor < m_max_length) {
                m_buffer[m_cursor++] = (char)raw.code;
                m_buffer[m_cursor] = '\0';
                set_paint_dirty();
            }
        }
    }
}

void TextBox::update(u64 delta_ms) {
    m_cursor_blink_time += (u32)delta_ms;
    if (m_cursor_blink_time >= 500) {
        m_cursor_visible = !m_cursor_visible;
        m_cursor_blink_time = 0;
        if (m_state == WidgetState::Focused) set_paint_dirty();
    }
}

void TextBox::set_text(const char* text) {
    if (!text) {
        m_buffer[0] = '\0';
        m_cursor = 0;
    } else {
        usize i = 0;
        while (text[i] && i < m_max_length) {
            m_buffer[i] = text[i];
            i++;
        }
        m_buffer[i] = '\0';
        m_cursor = i;
    }
    set_paint_dirty();
}

void TextBox::clear() {
    m_buffer[0] = '\0';
    m_cursor = 0;
    set_paint_dirty();
}

} // namespace acos::gui::widgets
