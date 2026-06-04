#include "layout_node.h"
#include "context.h"

namespace acos::ui {

LayoutNode::LayoutNode() : m_size{0,0}, m_position{0,0}, m_flex(0),
    m_parent(Ref<LayoutNode>::null()), m_first_child(Ref<LayoutNode>::null()),
    m_last_child(Ref<LayoutNode>::null()), m_next_sibling(Ref<LayoutNode>::null()) {}

void LayoutNode::add_child(UIContext* ctx, Ref<LayoutNode> self, Ref<LayoutNode> child) {
    if (child.is_null()) return;
    child.get(ctx)->m_parent = self;
    if (m_first_child.is_null()) { m_first_child = m_last_child = child; }
    else { m_last_child.get(ctx)->m_next_sibling = child; m_last_child = child; }
}

} // namespace acos::ui
