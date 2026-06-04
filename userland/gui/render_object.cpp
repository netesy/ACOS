#include "render_object.h"
#include "context.h"

namespace acos::ui {

RenderObject::RenderObject() : m_size{0,0}, m_position{0,0},
    m_parent(Ref<RenderObject>::null()), m_first_child(Ref<RenderObject>::null()),
    m_last_child(Ref<RenderObject>::null()), m_next_sibling(Ref<RenderObject>::null()) {}

bool RenderObject::hit_test([[maybe_unused]] UIContext* ctx, Position point, Position offset) {
    Position local = { offset.x + m_position.x, offset.y + m_position.y };
    return point.x >= local.x && point.x < local.x + m_size.w && point.y >= local.y && point.y < local.y + m_size.h;
}

void RenderObject::add_child(UIContext* ctx, Ref<RenderObject> self, Ref<RenderObject> child) {
    if (child.is_null()) return;
    child.get(ctx)->m_parent = self;
    if (m_first_child.is_null()) { m_first_child = m_last_child = child; }
    else { m_last_child.get(ctx)->m_next_sibling = child; m_last_child = child; }
}

} // namespace acos::ui
