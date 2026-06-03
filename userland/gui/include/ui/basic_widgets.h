#pragma once
#include <ui/widget.h>
#include <ui/layout_node.h>
#include <ui/render_object.h>
#include <ui/context.h>

namespace acos::ui {

class ColumnLayoutNode : public LayoutNode {
public:
    Size perform_layout([[maybe_unused]] UIContext* ctx, Constraints constraints) override {
        i32 current_y = 0;
        m_size = { constraints.max_w, current_y };
        return m_size;
    }
};

class ColumnRenderObject : public RenderObject {
public:
    void paint([[maybe_unused]] UIContext* ctx, [[maybe_unused]] acos::graphics::Renderer* renderer, [[maybe_unused]] Position offset) override {
    }
    bool hit_test([[maybe_unused]] UIContext* ctx, [[maybe_unused]] Position point, [[maybe_unused]] Position offset) override {
        return false;
    }
};

class Column : public Widget {
public:
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override {
        return ctx->make<ColumnLayoutNode>();
    }
    Ref<RenderObject> create_render_object(UIContext* ctx) override {
        return ctx->make<ColumnRenderObject>();
    }

    Column& child([[maybe_unused]] Ref<Widget> w) {
        return *this;
    }
};

} // namespace acos::ui
