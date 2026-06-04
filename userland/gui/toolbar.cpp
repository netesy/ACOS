#include "toolbar.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ToolBar::ToolBar() {
    m_rect.h = 40;
}


Ref<RenderObject> Toolbar::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> ToolBar::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
