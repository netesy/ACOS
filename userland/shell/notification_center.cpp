#include "notification_center.h"
#include "context.h"

namespace acos::shell {
NotificationCenter::NotificationCenter() {}
ui::Ref<ui::LayoutNode> NotificationCenter::create_layout_node(ui::UIContext* ctx) { return ctx->make<ui::LeafLayoutNode>(); }
ui::Ref<ui::RenderObject> NotificationCenter::create_render_object(ui::UIContext* ctx) { return ctx->make<ui::ContainerRenderObject>(); }
}
