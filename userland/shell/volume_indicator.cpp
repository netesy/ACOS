#include "volume_indicator.h"
#include "context.h"

namespace acos::shell {
VolumeIndicator::VolumeIndicator() {}
ui::Ref<ui::LayoutNode> VolumeIndicator::create_layout_node(ui::UIContext* ctx) { return ctx->make<ui::LeafLayoutNode>(); }
ui::Ref<ui::RenderObject> VolumeIndicator::create_render_object(ui::UIContext* ctx) { return ctx->make<ui::ContainerRenderObject>(); }
}
