#include "icon.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Icon::Icon() {
    m_rect = {0, 0, 100, 100};
}

Icon::~Icon() {}

Ref<RenderObject> Icon::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
