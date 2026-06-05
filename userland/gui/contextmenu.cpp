#include "contextmenu.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

ContextMenu::ContextMenu() {
    m_rect = {0, 0, 100, 100};
}

ContextMenu::~ContextMenu() {}

Ref<RenderObject> ContextMenu::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
