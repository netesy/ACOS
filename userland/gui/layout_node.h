#pragma once
#include "geometry.h"
#include "ref.h"

namespace acos::ui {

class UIContext;

class LayoutNode {
public:
    LayoutNode();
    virtual ~LayoutNode() = default;
    virtual Size perform_layout(UIContext* ctx, Constraints constraints) = 0;

    Size size() const { return m_size; }
    void set_size(Size s) { m_size = s; }

    Position position() const { return m_position; }
    void set_position(Position p) { m_position = p; }

    u32 flex() const { return m_flex; }
    void set_flex(u32 f) { m_flex = f; }

    Ref<LayoutNode> parent() const { return m_parent; }
    Ref<LayoutNode> first_child() const { return m_first_child; }
    Ref<LayoutNode> next_sibling() const { return m_next_sibling; }

    void add_child(UIContext* ctx, Ref<LayoutNode> self, Ref<LayoutNode> child);

protected:
    Size m_size; Position m_position; u32 m_flex;
    Ref<LayoutNode> m_parent, m_first_child, m_last_child, m_next_sibling;
};

} // namespace acos::ui
