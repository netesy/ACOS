#include "toolbutton.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ToolButton::ToolButton(const char* label) : Button(label) {
    m_rect.w = 32;
    m_rect.h = 32;
}


Ref<RenderObject> Toolbutton::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> ToolButton::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
