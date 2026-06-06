#include "link.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Link::Link(const char* text) : Label(text) {
}

Link::~Link() {}

Ref<RenderObject> Link::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
