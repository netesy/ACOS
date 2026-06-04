#include "tooltip.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Tooltip::Tooltip() : m_text(nullptr) {
    m_rect.w = 120;
    m_rect.h = 24;
    m_elevation = 16;
}


Ref<RenderObject> Tooltip::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> ToolTip::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
