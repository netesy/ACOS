#include "launcher.h"
#include "context.h"

namespace acos::shell {
Launcher::Launcher() {}
ui::Ref<ui::LayoutNode> Launcher::create_layout_node(ui::UIContext* ctx) { return ctx->make<ui::LeafLayoutNode>(); }
ui::Ref<ui::RenderObject> Launcher::create_render_object(ui::UIContext* ctx) { return ctx->make<ui::ContainerRenderObject>(); }
}
