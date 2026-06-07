#include "flex.h"
#include "render_object.h"
#include "context.h"

namespace acos::gui::widgets {

Size Flex::layout(BoxConstraints constraints) {
    ::acos::i32 main_total = 0;
    ::acos::i32 cross_max = 0;

    u32 visible_count = 0;
    for (auto& child : m_children) {
        if (child && child->is_visible()) visible_count++;
    }

    if (visible_count > 0) {
        main_total += (::acos::i32)(visible_count - 1) * m_spacing;
    }

    for (auto& child : m_children) {
        if (!child || !child->is_visible()) continue;

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

    ::acos::i32 main_max = (m_axis == Axis::Horizontal ? constraints.max_w : constraints.max_h);
    if (main_max >= BoxConstraints::Infinity) main_max = main_total;

    Size self_size = constraints.constrain(m_axis == Axis::Horizontal ? Size{main_max, cross_max} : Size{cross_max, main_max});
    m_rect.w = self_size.w;
    m_rect.h = self_size.h;

    ::acos::i32 main_offset = 0;
    ::acos::i32 between_spacing = m_spacing;

    if (m_main_axis_alignment == MainAxisAlignment::Center) {
        main_offset = (m_axis == Axis::Horizontal ? m_rect.w - main_total : m_rect.h - main_total) / 2;
    } else if (m_main_axis_alignment == MainAxisAlignment::End) {
        main_offset = (m_axis == Axis::Horizontal ? m_rect.w - main_total : m_rect.h - main_total);
    } else if (m_main_axis_alignment == MainAxisAlignment::SpaceBetween && visible_count > 1) {
        between_spacing = (m_axis == Axis::Horizontal ? m_rect.w - (main_total - (::acos::i32)(visible_count - 1) * m_spacing) : m_rect.h - (main_total - (::acos::i32)(visible_count - 1) * m_spacing)) / (::acos::i32)(visible_count - 1);
    }

    ::acos::i32 current_main = main_offset;
    for (auto& child : m_children) {
        if (!child || !child->is_visible()) continue;
        Size child_size = {child->rect().w, child->rect().h};

        ::acos::i32 cross_offset = 0;
        if (m_cross_axis_alignment == CrossAxisAlignment::Center) {
            cross_offset = (m_axis == Axis::Horizontal ? m_rect.h - child_size.h : m_rect.w - child_size.w) / 2;
        } else if (m_cross_axis_alignment == CrossAxisAlignment::End) {
            cross_offset = (m_axis == Axis::Horizontal ? m_rect.h - child_size.h : m_rect.w - child_size.w);
        }

        if (m_axis == Axis::Horizontal) {
            child->set_position(m_rect.x + current_main, m_rect.y + cross_offset);
            current_main += child_size.w + between_spacing;
        } else {
            child->set_position(m_rect.x + cross_offset, m_rect.y + current_main);
            current_main += child_size.h + between_spacing;
        }
    }

    clear_layout_dirty();
    return self_size;
}

} // namespace acos::gui::widgets
