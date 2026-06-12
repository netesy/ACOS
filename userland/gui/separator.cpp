#include <acos/process.h>
#include <acos/runtime.h>
#include "separator.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Separator::Separator(Orientation orient) : m_orientation(orient) {
    m_rect = {0, 0, 100, 2};
}

Separator::~Separator() {}

Ref<RenderObject> Separator::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
