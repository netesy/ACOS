#pragma once
#include "widget.h"
#include "layout_node.h"
#include "render_object.h"
#include "context.h"

namespace acos::ui {

class LeafLayoutNode : public LayoutNode {
public:
    Size perform_layout([[maybe_unused]] UIContext* ctx, Constraints constraints) override {
        m_size = constraints.satisfy({0, 0}); return m_size;
    }
};

class ContainerRenderObject : public RenderObject {
public:
    void paint(UIContext* ctx, acos::graphics::Renderer* renderer, Position offset) override {
        Position local_offset = { offset.x + m_position.x, offset.y + m_position.y };
        Ref<RenderObject> child = first_child();
        while (!child.is_null()) {
            RenderObject* child_obj = child.get(ctx);
            child_obj->paint(ctx, renderer, local_offset);
            child = child_obj->next_sibling();
        }
    }
};

class ColumnLayoutNode : public LayoutNode {
public:
    Size perform_layout(UIContext* ctx, Constraints constraints) override {
        i32 total_flex = 0, fixed_height = 0, max_w = 0;
        Ref<LayoutNode> child = first_child();
        while (!child.is_null()) {
            LayoutNode* node = child.get(ctx);
            if (node->flex() > 0) total_flex += node->flex();
            else {
                Size s = node->perform_layout(ctx, {0, constraints.max_w, 0, constraints.max_h - fixed_height});
                fixed_height += s.h; if (s.w > max_w) max_w = s.w;
            }
            child = node->next_sibling();
        }
        i32 remaining = constraints.max_h - fixed_height; if (remaining < 0) remaining = 0;
        i32 cur_y = 0; child = first_child();
        while (!child.is_null()) {
            LayoutNode* node = child.get(ctx);
            if (node->flex() > 0) {
                i32 ch = (remaining * (i32)node->flex()) / (total_flex > 0 ? total_flex : 1);
                Size s = node->perform_layout(ctx, {constraints.max_w, constraints.max_w, ch, ch});
                node->set_position({0, cur_y}); cur_y += s.h; if (s.w > max_w) max_w = s.w;
            } else { node->set_position({0, cur_y}); cur_y += node->size().h; }
            child = node->next_sibling();
        }
        m_size = constraints.satisfy({max_w, cur_y}); return m_size;
    }
};

class RowLayoutNode : public LayoutNode {
public:
    Size perform_layout(UIContext* ctx, Constraints constraints) override {
        i32 total_flex = 0, fixed_width = 0, max_h = 0;
        Ref<LayoutNode> child = first_child();
        while (!child.is_null()) {
            LayoutNode* node = child.get(ctx);
            if (node->flex() > 0) total_flex += node->flex();
            else {
                Size s = node->perform_layout(ctx, {0, constraints.max_w - fixed_width, 0, constraints.max_h});
                fixed_width += s.w; if (s.h > max_h) max_h = s.h;
            }
            child = node->next_sibling();
        }
        i32 remaining = constraints.max_w - fixed_width; if (remaining < 0) remaining = 0;
        i32 cur_x = 0; child = first_child();
        while (!child.is_null()) {
            LayoutNode* node = child.get(ctx);
            if (node->flex() > 0) {
                i32 cw = (remaining * (i32)node->flex()) / (total_flex > 0 ? total_flex : 1);
                Size s = node->perform_layout(ctx, {cw, cw, constraints.max_h, constraints.max_h});
                node->set_position({cur_x, 0}); cur_x += s.w; if (s.h > max_h) max_h = s.h;
            } else { node->set_position({cur_x, 0}); cur_x += node->size().w; }
            child = node->next_sibling();
        }
        m_size = constraints.satisfy({cur_x, max_h}); return m_size;
    }
};

class PaddingLayoutNode : public LayoutNode {
public:
    PaddingLayoutNode(i32 p) : m_padding(p) {}
    Size perform_layout(UIContext* ctx, Constraints constraints) override {
        i32 p2 = m_padding * 2;
        Constraints inner = {
            constraints.min_w > p2 ? constraints.min_w - p2 : 0, constraints.max_w > p2 ? constraints.max_w - p2 : 0,
            constraints.min_h > p2 ? constraints.min_h - p2 : 0, constraints.max_h > p2 ? constraints.max_h - p2 : 0
        };
        Ref<LayoutNode> child = first_child();
        if (!child.is_null()) {
            LayoutNode* c = child.get(ctx); Size s = c->perform_layout(ctx, inner);
            c->set_position({m_padding, m_padding}); m_size = constraints.satisfy({s.w + p2, s.h + p2});
        } else m_size = constraints.satisfy({p2, p2});
        return m_size;
    }
private:
    i32 m_padding;
};

class Column : public Widget {
public:
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<ColumnLayoutNode>(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
};
class Row : public Widget {
public:
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<RowLayoutNode>(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
};
class Padding : public Widget {
public:
    Padding(i32 p) : m_padding(p) {}
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<PaddingLayoutNode>(m_padding); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
private:
    i32 m_padding;
};
class Spacer : public Widget {
public:
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { auto n = ctx->make<LeafLayoutNode>(); n.get(ctx)->set_flex(1); return n; }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
};

} // namespace acos::ui
