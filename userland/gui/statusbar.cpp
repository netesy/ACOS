#include "statusbar.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

StatusBar::StatusBar() : m_text("Ready") {
    m_rect.h = 24;
}


Ref<RenderObject> Statusbar::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> StatusBar::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
