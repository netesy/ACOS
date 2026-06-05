#include "panel.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Panel::Panel() {
    m_rect = {0, 0, 100, 100};
}

Panel::~Panel() {}

Ref<RenderObject> Panel::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
