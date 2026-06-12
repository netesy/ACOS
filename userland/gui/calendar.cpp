#include <acos/process.h>
#include <acos/runtime.h>
#include "calendar.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Calendar::Calendar() {
    m_rect = {0, 0, 100, 100};
}

Calendar::~Calendar() {}

Ref<RenderObject> Calendar::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
