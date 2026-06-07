#include "text.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

Text::Text(const char* text) : m_text_color(0xFFFFFFFF), m_alignment(TextAlignment::Left), m_font_size(14) {
    m_rect = {0, 0, 100, 20};
    set_text(text);
}

Text::~Text() {}

void Text::set_text(const char* text) {
    if (!text) {
        m_text_buffer[0] = '\0';
        m_rect.w = 0;
        m_rect.h = 0;
    } else {
        usize i = 0;
        while (text[i] && i < 127) {
            m_text_buffer[i] = text[i];
            i++;
        }
        m_text_buffer[i] = '\0';

        u32 w, h;
        ::acos::graphics::Font::measure_string_default(m_text_buffer, w, h);
        m_rect.w = (i32)w;
        m_rect.h = (i32)h;
    }
    set_paint_dirty();
    set_layout_dirty();
}

Ref<RenderObject> Text::create_render_object() {
    return UIContext::get().region().alloc<RenderText>();
}

void Text::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rt = static_cast<RenderText*>(render_object.operator->());
    if (rt) {
        rt->set_text(m_text_buffer);
        rt->set_alignment(m_alignment);
    }
}

} // namespace acos::gui::widgets
