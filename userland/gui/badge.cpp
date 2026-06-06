#include "badge.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Badge::Badge(const char* text) : m_text(text) {
    m_rect = {0, 0, 100, 100};
}

Badge::~Badge() {}

Ref<RenderObject> Badge::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
