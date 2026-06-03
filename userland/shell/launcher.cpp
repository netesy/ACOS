#include "launcher.h"
#include <ui/context.h>

namespace acos::shell {

Launcher::Launcher() {}

ui::Ref<ui::LayoutNode> Launcher::create_layout_node([[maybe_unused]] ui::UIContext* ctx) {
    return ctx->make<ui::ColumnLayoutNode>();
}

ui::Ref<ui::RenderObject> Launcher::create_render_object([[maybe_unused]] ui::UIContext* ctx) {
    return ctx->make<ui::ColumnRenderObject>();
}

} // namespace acos::shell
