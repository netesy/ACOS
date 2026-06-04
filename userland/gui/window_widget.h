#pragma once
#include "widget.h"
#include "basic_widgets.h"

namespace acos::ui {

class WindowWidget : public Widget {
public:
    WindowWidget([[maybe_unused]] const char* title, [[maybe_unused]] i32 x, [[maybe_unused]] i32 y, [[maybe_unused]] i32 w, [[maybe_unused]] i32 h) {}
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<ColumnLayoutNode>(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
};

} // namespace acos::ui
