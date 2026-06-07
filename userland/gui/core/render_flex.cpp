#include "flex.h"
#include "render_object.h"
#include "context.h"

namespace acos::gui::widgets {

class RenderFlex : public RenderObject {
public:
    RenderFlex(::acos::gui::Axis axis, ::acos::gui::MainAxisAlignment main_align, ::acos::gui::CrossAxisAlignment cross_align, ::acos::i32 spacing)
        : m_axis(axis), m_main_align(main_align), m_cross_align(cross_align), m_spacing(spacing) {}

    void paint(::acos::graphics::Renderer* renderer) override {
        for (auto& child : m_children) {
            if (child) child->paint(renderer);
        }
    }

    void perform_layout(BoxConstraints constraints) override {
        ::acos::i32 main_total = 0;
        ::acos::i32 cross_max = 0;

        u32 visible_count = 0;
        for (auto& child : m_children) {
            if (child) visible_count++;
        }

        if (visible_count > 0) {
            main_total += (::acos::i32)(visible_count - 1) * m_spacing;
        }

        for (auto& child : m_children) {
            if (!child) continue;

            BoxConstraints child_constraints = BoxConstraints::loose(
                m_axis == ::acos::gui::Axis::Horizontal ? constraints.max_w - main_total : constraints.max_w,
                m_axis == ::acos::gui::Axis::Vertical ? constraints.max_h - main_total : constraints.max_h
            );

            child->perform_layout(child_constraints);
            Size child_size = {child->rect().w, child->rect().h};

            if (m_axis == ::acos::gui::Axis::Horizontal) {
                main_total += child_size.w;
                if (child_size.h > cross_max) cross_max = child_size.h;
            } else {
                main_total += child_size.h;
                if (child_size.w > cross_max) cross_max = child_size.w;
            }
        }

        ::acos::i32 main_max = (m_axis == ::acos::gui::Axis::Horizontal ? constraints.max_w : constraints.max_h);
        if (main_max >= BoxConstraints::Infinity) main_max = main_total;

        Size self_size = constraints.constrain(m_axis == ::acos::gui::Axis::Horizontal ? Size{main_max, cross_max} : Size{cross_max, main_max});
        m_rect.w = self_size.w;
        m_rect.h = self_size.h;

        ::acos::i32 main_offset = 0;
        if (m_main_align == ::acos::gui::MainAxisAlignment::Center) {
            main_offset = (m_axis == ::acos::gui::Axis::Horizontal ? m_rect.w - main_total : m_rect.h - main_total) / 2;
        } else if (m_main_align == ::acos::gui::MainAxisAlignment::End) {
            main_offset = (m_axis == ::acos::gui::Axis::Horizontal ? m_rect.w - main_total : m_rect.h - main_total);
        }

        ::acos::i32 current_main = main_offset;
        for (auto& child : m_children) {
            if (!child) continue;
            Size child_size = {child->rect().w, child->rect().h};

            ::acos::i32 cross_offset = 0;
            if (m_cross_align == ::acos::gui::CrossAxisAlignment::Center) {
                cross_offset = (m_axis == ::acos::gui::Axis::Horizontal ? m_rect.h - child_size.h : m_rect.w - child_size.w) / 2;
            } else if (m_cross_align == ::acos::gui::CrossAxisAlignment::End) {
                cross_offset = (m_axis == ::acos::gui::Axis::Horizontal ? m_rect.h - child_size.h : m_rect.w - child_size.w);
            }

            if (m_axis == ::acos::gui::Axis::Horizontal) {
                child->set_rect({m_rect.x + current_main, m_rect.y + cross_offset, child_size.w, child_size.h});
                current_main += child_size.w + m_spacing;
            } else {
                child->set_rect({m_rect.x + cross_offset, m_rect.y + current_main, child_size.w, child_size.h});
                current_main += child_size.h + m_spacing;
            }
        }
    }

private:
    ::acos::gui::Axis m_axis;
    ::acos::gui::MainAxisAlignment m_main_align;
    ::acos::gui::CrossAxisAlignment m_cross_align;
    ::acos::i32 m_spacing;
};

Ref<RenderObject> Flex::create_render_object() {
    return UIContext::get().region().alloc<RenderFlex>(m_axis, m_main_axis_alignment, m_cross_axis_alignment, m_spacing);
}

} // namespace acos::gui::widgets
