#include "flex.h"
#include "render_object.h"
#include "context.h"

namespace acos::gui::widgets {

Size Flex::layout(BoxConstraints constraints) {
    i32 main_total = 0;
    i32 cross_max = 0;
    u32 visible_children = 0;

    for (auto& child : m_children) {
        if (!child || !child->is_visible()) continue;
        visible_children++;

        BoxConstraints child_constraints;
        if (m_axis == Axis::Horizontal) {
            child_constraints = BoxConstraints::loose(constraints.max_w - main_total, constraints.max_h);
        } else {
            child_constraints = BoxConstraints::loose(constraints.max_w, constraints.max_h - main_total);
        }

        Size child_size = child->layout(child_constraints);

        if (m_axis == Axis::Horizontal) {
            main_total += child_size.w;
            if (child_size.h > cross_max) cross_max = child_size.h;
        } else {
            main_total += child_size.h;
            if (child_size.w > cross_max) cross_max = child_size.w;
        }
    }

    Size self_size = constraints.constrain(m_axis == Axis::Horizontal ? Size{main_total, cross_max} : Size{cross_max, main_total});
    m_rect.w = self_size.w;
    m_rect.h = self_size.h;

    i32 current_main = 0;
    for (auto& child : m_children) {
        if (!child || !child->is_visible()) continue;
        Size child_size = {child->rect().w, child->rect().h};
        if (m_axis == Axis::Horizontal) {
            child->set_position(m_rect.x + current_main, m_rect.y);
            current_main += child_size.w;
        } else {
            child->set_position(m_rect.x, m_rect.y + current_main);
            current_main += child_size.h;
        }
    }

    clear_layout_dirty();
    return self_size;
}

} // namespace acos::gui::widgets
