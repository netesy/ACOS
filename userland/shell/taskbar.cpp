#include "taskbar.h"
#include <ui/context.h>

namespace acos::shell {

Taskbar::Taskbar() {
    m_clock_str[0] = '\0';
}

ui::Ref<ui::LayoutNode> Taskbar::create_layout_node([[maybe_unused]] ui::UIContext* ctx) {
    return ctx->make<ui::ColumnLayoutNode>();
}

ui::Ref<ui::RenderObject> Taskbar::create_render_object([[maybe_unused]] ui::UIContext* ctx) {
    return ctx->make<ui::ColumnRenderObject>();
}

void Taskbar::update_clock() {
}

} // namespace acos::shell
