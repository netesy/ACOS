#include "dialog.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Dialog::Dialog() {
    m_rect = {0, 0, 100, 100};
}

Dialog::~Dialog() {}

Ref<RenderObject> Dialog::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
