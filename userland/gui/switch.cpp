#include "switch.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Switch::Switch() {
    m_rect = {0, 0, 100, 100};
}

Switch::~Switch() {}

Ref<RenderObject> Switch::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
