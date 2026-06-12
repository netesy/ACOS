#pragma once
#include <acos/graphics.h>
#include "ref.h"
#include "vector.h"
#include "layout_types.h"
#include "style.h"
#include "compositor.h"

namespace acos::gui {

struct Rect {
    ::acos::i32 x, y, w, h;
    bool contains(::acos::i32 px, ::acos::i32 py) const {
        return px >= x && px < x + w && py >= y && py < y + h;
    }
};

class RenderObject {
public:
    RenderObject() : m_rect{0, 0, 0, 0}, m_parent(), m_style() {}
    virtual ~RenderObject() {}

    virtual void paint(::acos::graphics::Renderer* renderer) = 0;
    virtual void perform_layout(BoxConstraints constraints) = 0;

    void set_rect(const Rect& rect) { m_rect = rect; }
    Rect rect() const { return m_rect; }

    void add_child(Ref<RenderObject> child) {
        m_children.push_back(child);
        child->set_parent(self());
    }

    void set_parent(Ref<RenderObject> parent) { m_parent = parent; }
    Ref<RenderObject> parent() const { return m_parent; }
    const ::acos::Vector<Ref<RenderObject>>& children() const { return m_children; }
    void clear_children() { m_children.clear(); }

    Ref<RenderObject> self();

    void set_style(const Style& style) { m_style = style; }
    Style style() const { return m_style; }

    virtual CompositorLayer* layer() { return nullptr; }

protected:
    Rect m_rect;
    Ref<RenderObject> m_parent;
    ::acos::Vector<Ref<RenderObject>> m_children;
    Style m_style;
};

} // namespace acos::gui
