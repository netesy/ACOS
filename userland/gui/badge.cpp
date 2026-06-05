#include "badge.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

Badge::Badge(const char* text) : m_text(text) {
    m_rect.w = 20;
    m_rect.h = 20;
}


Ref<RenderObject> Badge::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
