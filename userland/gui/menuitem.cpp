#include "menuitem.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

MenuItem::MenuItem(const char* label) : m_label(label) {
    m_rect.h = 24;
}



Ref<RenderObject> Menuitem::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> MenuItem::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
