#pragma once
#include <ui/widget.h>
#include <ui/basic_widgets.h>

namespace acos::ui {

class WindowWidget : public Widget {
public:
    WindowWidget([[maybe_unused]] const char* title, [[maybe_unused]] i32 x, [[maybe_unused]] i32 y, [[maybe_unused]] i32 w, [[maybe_unused]] i32 h) {}
    Ref<LayoutNode> create_layout_node([[maybe_unused]] UIContext* ctx) override { return ctx->make<ColumnLayoutNode>(); }
    Ref<RenderObject> create_render_object([[maybe_unused]] UIContext* ctx) override { return ctx->make<ColumnRenderObject>(); }

    WindowWidget& title([[maybe_unused]] const char* t) { return *this; }
    template<typename T>
    WindowWidget& child([[maybe_unused]] Ref<T> w) { return *this; }
};

} // namespace acos::ui
