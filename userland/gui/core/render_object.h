#pragma once
#include <kernel/graphics/renderer.h>
#include "ref.h"
#include "vector.h"
#include "layout_types.h"
#include "../widget.h"

namespace acos::gui {

class RenderObject {
public:
    RenderObject() : m_rect{0, 0, 0, 0}, m_parent() {}
    virtual ~RenderObject() {}

    virtual void paint(acos::graphics::Renderer* renderer) = 0;
    virtual void perform_layout(BoxConstraints constraints) = 0;

    void set_rect(const Rect& rect) { m_rect = rect; }
    Rect rect() const { return m_rect; }

    void add_child(Ref<RenderObject> child) {
        m_children.push_back(child);
        child->set_parent(self());
    }

    void set_parent(Ref<RenderObject> parent) { m_parent = parent; }
    Ref<RenderObject> parent() const { return m_parent; }

    Ref<RenderObject> self();

protected:
    Rect m_rect;
    Ref<RenderObject> m_parent;
    Vector<Ref<RenderObject>> m_children;
};

} // namespace acos::gui
