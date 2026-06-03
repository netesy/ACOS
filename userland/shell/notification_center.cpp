#include "notification_center.h"
#include <ui/context.h>

namespace acos::shell {

NotificationCenter::NotificationCenter() {}

ui::Ref<ui::LayoutNode> NotificationCenter::create_layout_node([[maybe_unused]] ui::UIContext* ctx) {
    return ctx->make<ui::ColumnLayoutNode>();
}

ui::Ref<ui::RenderObject> NotificationCenter::create_render_object([[maybe_unused]] ui::UIContext* ctx) {
    return ctx->make<ui::ColumnRenderObject>();
}

} // namespace acos::shell
