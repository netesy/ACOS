#include <acos/process.h>
#include <acos/runtime.h>
#include "toolbutton.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

ToolButton::ToolButton(const char* label) : Button(label) {
    m_rect = {0, 0, 100, 100};
}

ToolButton::~ToolButton() {}

Ref<RenderObject> ToolButton::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
