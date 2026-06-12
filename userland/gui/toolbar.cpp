#include <acos/process.h>
#include <acos/runtime.h>
#include "toolbar.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

ToolBar::ToolBar() {
    m_rect = {0, 0, 800, 32};
}

ToolBar::~ToolBar() {}

Ref<RenderObject> ToolBar::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
