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
        rt->set_cursor(m_cursor_pos, m_cursor_visible);
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
    } else {
        usize i = 0;
        while (text[i] && i < 4095) {
            m_buffer[i] = text[i];
            i++;
        }
        m_buffer[i] = '\0';
    }
    set_paint_dirty();
}

} // namespace acos::gui::widgets
