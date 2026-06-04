#include "flex.h"

namespace acos::gui {

Size Flex::layout(BoxConstraints constraints) {
    i32 main_total = 0;
    i32 cross_max = 0;
    u32 visible_children = 0;

    // First pass: layout children with loose constraints on main axis
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

    // Second pass: position children
    i32 current_main = 0;
    i32 spacing = 0;
    i32 main_size = (m_axis == Axis::Horizontal) ? self_size.w : self_size.h;
    i32 remaining = main_size - main_total;

    if (visible_children > 1) {
        if (m_main_axis_alignment == MainAxisAlignment::SpaceBetween) {
            spacing = remaining / (visible_children - 1);
        } else if (m_main_axis_alignment == MainAxisAlignment::SpaceAround) {
            spacing = remaining / visible_children;
            current_main = spacing / 2;
        } else if (m_main_axis_alignment == MainAxisAlignment::SpaceEvenly) {
            spacing = remaining / (visible_children + 1);
            current_main = spacing;
        }
    }

    if (spacing == 0) {
        if (m_main_axis_alignment == MainAxisAlignment::Center) current_main = remaining / 2;
        else if (m_main_axis_alignment == MainAxisAlignment::End) current_main = remaining;
    }

    for (auto& child : m_children) {
        if (!child || !child->is_visible()) continue;

        Size child_size = {child->rect().w, child->rect().h};
        i32 cross_pos = 0;

        if (m_axis == Axis::Horizontal) {
            if (m_cross_axis_alignment == CrossAxisAlignment::Center) cross_pos = (self_size.h - child_size.h) / 2;
            else if (m_cross_axis_alignment == CrossAxisAlignment::End) cross_pos = self_size.h - child_size.h;
            else if (m_cross_axis_alignment == CrossAxisAlignment::Stretch) {
                child->layout(BoxConstraints::tight(child_size.w, self_size.h));
            }
            child->set_position(m_rect.x + current_main, m_rect.y + cross_pos);
            current_main += child_size.w + spacing;
        } else {
            if (m_cross_axis_alignment == CrossAxisAlignment::Center) cross_pos = (self_size.w - child_size.w) / 2;
            else if (m_cross_axis_alignment == CrossAxisAlignment::End) cross_pos = self_size.w - child_size.w;
            else if (m_cross_axis_alignment == CrossAxisAlignment::Stretch) {
                child->layout(BoxConstraints::tight(self_size.w, child_size.h));
            }
            child->set_position(m_rect.x + cross_pos, m_rect.y + current_main);
            current_main += child_size.h + spacing;
        }
    }

    clear_layout_dirty();
    return self_size;
}

void Flex::draw(acos::graphics::Renderer* renderer) {
    for (auto& child : m_children) {
        if (child && child->is_visible()) {
            child->draw(renderer);
        }
    }
}

} // namespace acos::gui
