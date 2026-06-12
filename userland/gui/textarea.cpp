#include <acos/process.h>
#include <acos/runtime.h>
#include "textarea.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

TextArea::TextArea() : m_cursor_pos(0), m_cursor_blink_time(0), m_cursor_visible(false) {
    m_rect = {0, 0, 200, 100};
    m_buffer[0] = '\0';
}

TextArea::~TextArea() {}

Ref<RenderObject> TextArea::create_render_object() {
    return UIContext::get().region().alloc<RenderTextArea>();
}

void TextArea::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rt = static_cast<RenderTextArea*>(render_object.operator->());
    if (rt) {
        rt->set_text(m_buffer);
        rt->set_cursor(m_cursor_pos, m_cursor_visible && (m_state == WidgetState::Focused));
    }
}

void TextArea::on_event(Event& event) {
    const auto& raw = event.raw;
    if (raw.type == acos::input::InputType::Mouse) {
        if (raw.value & 0x01) { // Left click
            UIContext::get().focus_manager().set_focus(self());
        }
    } else if (raw.type == acos::input::InputType::Keyboard && m_state == WidgetState::Focused) {
        if (raw.code == 8) { // Backspace
            backspace();
        } else if (raw.code == 13 || raw.code == 10) { // Enter
            insert_char('\n');
        } else if (raw.code >= 32 && raw.code <= 126) {
            insert_char((char)raw.code);
        }
    }
}

void TextArea::update(u64 delta_ms) {
    m_cursor_blink_time += (u32)delta_ms;
    if (m_cursor_blink_time >= 500) {
        m_cursor_visible = !m_cursor_visible;
        m_cursor_blink_time = 0;
        set_paint_dirty();
    }
}

void TextArea::set_text(const char* text) {
    if (!text) {
        m_buffer[0] = '\0';
        m_cursor_pos = 0;
    } else {
        usize i = 0;
        while (text[i] && i < 4095) {
            m_buffer[i] = text[i];
            i++;
        }
        m_buffer[i] = '\0';
        m_cursor_pos = (u32)i;
    }
    set_paint_dirty();
}

void TextArea::insert_char(char c) {
    if (m_cursor_pos < 4095) {
        // Simple append for now
        m_buffer[m_cursor_pos++] = c;
        m_buffer[m_cursor_pos] = '\0';
        set_paint_dirty();
    }
}

void TextArea::backspace() {
    if (m_cursor_pos > 0) {
        m_cursor_pos--;
        m_buffer[m_cursor_pos] = '\0';
        set_paint_dirty();
    }
}

} // namespace acos::gui::widgets
