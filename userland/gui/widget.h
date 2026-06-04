#pragma once
#include "ref.h"
#include "style.h"
#include "list.h"
#include "geometry.h"

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
    template<typename T> Widget& child(UIContext* ctx, Ref<T> c) { add_child(ctx, Ref<Widget>(c)); return *this; }

    // Compatibility methods for legacy apps
    void add_child(Widget*) {}
    void set_position(i32, i32) {}
    void set_size(i32, i32) {}

    const List<Ref<Widget>>& children() const { return m_children; }
    Ref<Widget> parent() const { return m_parent; }
    void set_parent(Ref<Widget> p) { m_parent = p; }

    bool is_dirty() const { return m_dirty; }
    void mark_dirty();
    void clear_dirty() { m_dirty = false; }

    Ref<LayoutNode> layout_node() const { return m_layout_node; }
    void set_layout_node(Ref<LayoutNode> ln) { m_layout_node = ln; }

    Ref<RenderObject> render_object() const { return m_render_object; }
    void set_render_object(Ref<RenderObject> ro) { m_render_object = ro; }

    // Fluent Modifiers
    Widget& background(u32 color);
    Widget& color(u32 color);
    Widget& radius(i32 r);
    Widget& padding(i32 p);
    Widget& flex(u32 f);
    u32 flex() const { return m_flex; }

protected:
    Ref<Widget> m_parent;
    List<Ref<Widget>> m_children;
    Style m_style;
    Ref<LayoutNode> m_layout_node;
    Ref<RenderObject> m_render_object;
    u32 m_flex = 0;
    bool m_dirty;
};

} // namespace acos::ui
