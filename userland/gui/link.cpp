#include "link.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Link::Link(const char* text) : Label(text) {
    m_rect.h = 20;
    m_flags |= (u32)WidgetFlags::Clickable;
}



Ref<RenderObject> Link::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
