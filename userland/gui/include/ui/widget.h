#pragma once
#include <ui/ref.h>
#include "kernel/graphics/types.h"

namespace acos::ui {

class RenderObject;
class LayoutNode;

class Widget {
public:
    Widget() : m_dirty(true), m_visible(true) {}
    virtual ~Widget() = default;

    bool is_dirty() const { return m_dirty; }
    void mark_dirty() { m_dirty = true; }
    void clear_dirty() { m_dirty = false; }

    bool is_visible() const { return m_visible; }
    void set_visible([[maybe_unused]] bool v) { m_visible = v; m_dirty = true; }

    Ref<Widget> parent() const { return m_parent; }
    void set_parent(Ref<Widget> p) { m_parent = p; }

    virtual Ref<LayoutNode> create_layout_node(UIContext* ctx) = 0;
    virtual Ref<RenderObject> create_render_object(UIContext* ctx) = 0;

    virtual void update_layout_node([[maybe_unused]] UIContext* ctx, [[maybe_unused]] Ref<LayoutNode> node) {}
    virtual void update_render_object([[maybe_unused]] UIContext* ctx, [[maybe_unused]] Ref<RenderObject> obj) {}

    // Temporary compatibility methods
    void add_child([[maybe_unused]] Widget* child) {}
    void set_position([[maybe_unused]] i32 x, [[maybe_unused]] i32 y) {}
    void set_size([[maybe_unused]] i32 w, [[maybe_unused]] i32 h) {}

protected:
    Ref<Widget> m_parent = Ref<Widget>::null();
    bool m_dirty;
    bool m_visible;
};

} // namespace acos::ui
