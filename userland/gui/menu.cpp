#include "menu.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Menu::Menu() {
    m_rect = {0, 0, 100, 100};
}

Menu::~Menu() {}

Ref<RenderObject> Menu::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
