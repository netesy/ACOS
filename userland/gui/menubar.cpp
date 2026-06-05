#include "menubar.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

MenuBar::MenuBar() {
    m_rect = {0, 0, 100, 100};
}

MenuBar::~MenuBar() {}

Ref<RenderObject> MenuBar::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
