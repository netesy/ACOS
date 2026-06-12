#include <acos/process.h>
#include <acos/runtime.h>
#include "badge.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

Badge::Badge(const char* text) : m_text(text) {
    m_rect = {0, 0, 80, 20};
}

Badge::~Badge() {}

Ref<RenderObject> Badge::create_render_object() {
    return UIContext::get().region().alloc<RenderBadge>();
}

void Badge::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rb = static_cast<RenderBadge*>(render_object.operator->());
    if (rb) {
        rb->set_text(m_text);
    }
}

} // namespace acos::gui::widgets
