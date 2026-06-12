#include <acos/process.h>
#include <acos/runtime.h>
#include "menuitem.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

MenuItem::MenuItem(const char* label) : m_label(label) {
    m_rect = {0, 0, 100, 100};
}

MenuItem::~MenuItem() {}

Ref<RenderObject> MenuItem::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
