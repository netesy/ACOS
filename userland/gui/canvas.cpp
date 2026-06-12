#include <acos/process.h>
#include <acos/runtime.h>
#include "canvas.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Canvas::Canvas() {
    m_rect = {0, 0, 100, 100};
}

Canvas::~Canvas() {}

Ref<RenderObject> Canvas::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
