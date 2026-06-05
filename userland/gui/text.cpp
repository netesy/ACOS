#include "text.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>
#include "core/render_widgets.h"

namespace acos::gui::widgets {

Text::Text(const char* text)
    : m_text(text), m_text_color(g_current_theme.text),
      m_alignment(TextAlignment::Left), m_font_size(16) {
    m_rect.w = 200;
    m_rect.h = 24;
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled;
}

Text::~Text() {}

Ref<RenderObject> Text::create_render_object() {
    Ref<RenderObject> ro = UIContext::get().region().alloc<RenderText>();
    update_render_object(ro);
    return ro;
}

void Text::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    if (render_object) {
        RenderText* rt = static_cast<RenderText*>(render_object.operator->());
        rt->set_text(m_text);
    }
}

} // namespace acos::gui::widgets
