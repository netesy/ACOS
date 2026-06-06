#include "contextmenu.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

ContextMenu::ContextMenu() {}

ContextMenu::~ContextMenu() {}

void ContextMenu::popup(::acos::i32 x, ::acos::i32 y) {
    set_position(x, y);
    set_visible(true);
}

Ref<RenderObject> ContextMenu::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
