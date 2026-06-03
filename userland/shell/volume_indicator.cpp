#include "volume_indicator.h"
#include <ui/context.h>

namespace acos::shell {

VolumeIndicator::VolumeIndicator() {}

ui::Ref<ui::LayoutNode> VolumeIndicator::create_layout_node([[maybe_unused]] ui::UIContext* ctx) {
    return ctx->make<ui::ColumnLayoutNode>();
}

ui::Ref<ui::RenderObject> VolumeIndicator::create_render_object([[maybe_unused]] ui::UIContext* ctx) {
    return ctx->make<ui::ColumnRenderObject>();
}

} // namespace acos::shell
