#include "link.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Link::Link() {
    m_rect = {0, 0, 100, 100};
}

Link::~Link() {}

Ref<RenderObject> Link::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
