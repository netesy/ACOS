#pragma once
#include "ref.h"
#include "style.h"
#include "list.h"
#include "geometry.h"
#include "kernel/graphics/renderer.h"

namespace acos::ui {

class LayoutNode;
class RenderObject;
class UIContext;

class Widget {
public:
    Widget();
    virtual ~Widget() = default;

    virtual Ref<LayoutNode> create_layout_node(UIContext* ctx) = 0;
    virtual Ref<RenderObject> create_render_object(UIContext* ctx) = 0;

    virtual void update_layout_node([[maybe_unused]] UIContext* ctx, [[maybe_unused]] Ref<LayoutNode> node) {}
    virtual void update_render_object([[maybe_unused]] UIContext* ctx, [[maybe_unused]] Ref<RenderObject> obj) {}
    virtual void build([[maybe_unused]] UIContext* ctx) {}

    void add_child(UIContext* ctx, Ref<Widget> child);

    void add_child([[maybe_unused]] Widget* child) {}
    void set_position([[maybe_unused]] i32 x, [[maybe_unused]] i32 y) {}
    void set_size([[maybe_unused]] i32 w, [[maybe_unused]] i32 h) {}
    void draw([[maybe_unused]] acos::graphics::Renderer* r) {}

    template<typename T> Widget& child(UIContext* ctx, Ref<T> c) { add_child(ctx, Ref<Widget>(c)); return *this; }

    Widget& background(u32 color);
    bool is_dirty() const { return m_dirty; }
    void mark_dirty() { m_dirty = true; }
    void clear_dirty() { m_dirty = false; }

    const List<Ref<Widget>>& children() const { return m_children; }

    Ref<LayoutNode> layout_node() const { return m_layout_node; }
    void set_layout_node(Ref<LayoutNode> ln) { m_layout_node = ln; }

    Ref<RenderObject> render_object() const { return m_render_object; }
    void set_render_object(Ref<RenderObject> ro) { m_render_object = ro; }

protected:
    Ref<Widget> m_parent;
    List<Ref<Widget>> m_children;
    Style m_style;
    Ref<LayoutNode> m_layout_node;
    Ref<RenderObject> m_render_object;
    bool m_dirty;
};

} // namespace acos::ui
