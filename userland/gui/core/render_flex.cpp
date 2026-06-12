#include <acos/process.h>
#include <acos/runtime.h>
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
        // Skip fixed/absolute children — they are handled by apply_positioned_layout
        auto is_out_of_flow = [](const Ref<RenderObject>& child) -> bool {
            if (!child) return true;
            const Style& s = child->style();
            return s.position == Position::Fixed || s.position == Position::Absolute;
        };

        // First pass: lay out fixed children to measure total fixed size
        ::acos::i32 main_fixed = 0;
        ::acos::i32 cross_max = 0;
        ::acos::u32 grow_total = 0;
        u32 visible_count = 0;

        for (auto& child : m_children) {
            if (!child || is_out_of_flow(child)) continue;
            visible_count++;
            grow_total += child->style().flex_grow;
        }

        if (visible_count > 0) {
            main_fixed += (::acos::i32)(visible_count - 1) * m_spacing;
        }

        // Layout non-growing in-flow children first
        for (auto& child : m_children) {
            if (!child || is_out_of_flow(child)) continue;
            if (child->style().flex_grow > 0) continue;

            ::acos::i32 ph = child->style().preferred_h;
            ::acos::i32 pw = child->style().preferred_w;
            // Apply margins to child available space
            ::acos::i32 ml = (::acos::i32)child->style().margin_left;
            ::acos::i32 mr = (::acos::i32)child->style().margin_right;
            ::acos::i32 mt = (::acos::i32)child->style().margin_top;
            ::acos::i32 mb = (::acos::i32)child->style().margin_bottom;

            BoxConstraints child_constraints;
            if (m_axis == ::acos::gui::Axis::Horizontal) {
                ::acos::i32 max_w = (pw > 0) ? pw : (constraints.max_w - ml - mr);
                ::acos::i32 max_h = (ph > 0) ? ph : (constraints.max_h - mt - mb);
                if (max_w < 0) max_w = 0;
                if (max_h < 0) max_h = 0;
                child_constraints = BoxConstraints::loose(max_w, max_h);
            } else {
                ::acos::i32 max_h = (ph > 0) ? ph : (constraints.max_h - mt - mb);
                ::acos::i32 max_w = (pw > 0) ? pw : (constraints.max_w - ml - mr);
                if (max_w < 0) max_w = 0;
                if (max_h < 0) max_h = 0;
                child_constraints = BoxConstraints::loose(max_w, max_h);
            }

            child->perform_layout(child_constraints);
            Size child_size = {child->rect().w, child->rect().h};

            if (m_axis == ::acos::gui::Axis::Horizontal) {
                main_fixed += child_size.w + ml + mr;
                ::acos::i32 total_h = child_size.h + mt + mb;
                if (total_h > cross_max) cross_max = total_h;
            } else {
                main_fixed += child_size.h + mt + mb;
                ::acos::i32 total_w = child_size.w + ml + mr;
                if (total_w > cross_max) cross_max = total_w;
            }
        }

        // Determine self size
        ::acos::i32 main_max = (m_axis == ::acos::gui::Axis::Horizontal ? constraints.max_w : constraints.max_h);
        if (main_max >= BoxConstraints::Infinity) main_max = main_fixed;

        // Self preferred size
        ::acos::i32 self_pw = m_style.preferred_w;
        ::acos::i32 self_ph = m_style.preferred_h;
        ::acos::i32 target_main = (m_axis == ::acos::gui::Axis::Horizontal)
            ? (self_pw > 0 ? self_pw : main_max)
            : (self_ph > 0 ? self_ph : main_max);
        ::acos::i32 target_cross = (m_axis == ::acos::gui::Axis::Horizontal)
            ? (self_ph > 0 ? self_ph : cross_max)
            : (self_pw > 0 ? self_pw : cross_max);

        Size self_size = constraints.constrain(
            m_axis == ::acos::gui::Axis::Horizontal
                ? Size{target_main, target_cross}
                : Size{target_cross, target_main}
        );
        m_rect.w = self_size.w;
        m_rect.h = self_size.h;

        // Distribute remaining space to flex_grow children
        ::acos::i32 avail_main = (m_axis == ::acos::gui::Axis::Horizontal ? m_rect.w : m_rect.h);
        ::acos::i32 remaining = avail_main - main_fixed;
        if (remaining < 0) remaining = 0;

        for (auto& child : m_children) {
            if (!child || is_out_of_flow(child) || child->style().flex_grow == 0) continue;

            ::acos::i32 share = (grow_total > 0)
                ? (remaining * (::acos::i32)child->style().flex_grow / (::acos::i32)grow_total)
                : 0;

            BoxConstraints child_constraints;
            if (m_axis == ::acos::gui::Axis::Horizontal) {
                child_constraints = BoxConstraints::tight(share, m_rect.h);
            } else {
                child_constraints = BoxConstraints::tight(m_rect.w, share);
            }

            child->perform_layout(child_constraints);
        }

        // --- Positioning pass ---
        // Compute total content size for alignment
        ::acos::i32 content_main = 0;
        for (auto& child : m_children) {
            if (!child || is_out_of_flow(child)) continue;
            ::acos::i32 ml = (::acos::i32)child->style().margin_left;
            ::acos::i32 mr = (::acos::i32)child->style().margin_right;
            ::acos::i32 mt = (::acos::i32)child->style().margin_top;
            ::acos::i32 mb = (::acos::i32)child->style().margin_bottom;
            if (m_axis == ::acos::gui::Axis::Horizontal)
                content_main += child->rect().w + ml + mr;
            else
                content_main += child->rect().h + mt + mb;
        }
        if (visible_count > 1) content_main += (::acos::i32)(visible_count - 1) * m_spacing;

        ::acos::i32 main_offset = 0;
        ::acos::i32 between_spacing = m_spacing;

        if (m_main_align == ::acos::gui::MainAxisAlignment::Center) {
            main_offset = (avail_main - content_main) / 2;
        } else if (m_main_align == ::acos::gui::MainAxisAlignment::End) {
            main_offset = avail_main - content_main;
        } else if (m_main_align == ::acos::gui::MainAxisAlignment::SpaceBetween && visible_count > 1) {
            ::acos::i32 items_w = 0;
            for (auto& child : m_children) {
                if (!child || is_out_of_flow(child)) continue;
                ::acos::i32 ml = (::acos::i32)child->style().margin_left;
                ::acos::i32 mr = (::acos::i32)child->style().margin_right;
                ::acos::i32 mt = (::acos::i32)child->style().margin_top;
                ::acos::i32 mb = (::acos::i32)child->style().margin_bottom;
                if (m_axis == ::acos::gui::Axis::Horizontal)
                    items_w += child->rect().w + ml + mr;
                else
                    items_w += child->rect().h + mt + mb;
            }
            between_spacing = (avail_main - items_w) / (::acos::i32)(visible_count - 1);
        }
        if (main_offset < 0) main_offset = 0;
        if (between_spacing < 0) between_spacing = 0;

        ::acos::i32 current_main = main_offset;
        ::acos::i32 cross_avail = (m_axis == ::acos::gui::Axis::Horizontal ? m_rect.h : m_rect.w);

        for (auto& child : m_children) {
            if (!child || is_out_of_flow(child)) continue;

            ::acos::i32 ml = (::acos::i32)child->style().margin_left;
            ::acos::i32 mr = (::acos::i32)child->style().margin_right;
            ::acos::i32 mt = (::acos::i32)child->style().margin_top;
            ::acos::i32 mb = (::acos::i32)child->style().margin_bottom;

            Size child_size = {child->rect().w, child->rect().h};

            ::acos::i32 cross_child = (m_axis == ::acos::gui::Axis::Horizontal)
                ? child_size.h + mt + mb
                : child_size.w + ml + mr;

            ::acos::i32 cross_offset = 0;
            if (m_cross_align == ::acos::gui::CrossAxisAlignment::Center) {
                cross_offset = (cross_avail - cross_child) / 2;
            } else if (m_cross_align == ::acos::gui::CrossAxisAlignment::End) {
                cross_offset = cross_avail - cross_child;
            } else if (m_cross_align == ::acos::gui::CrossAxisAlignment::Stretch) {
                if (m_axis == ::acos::gui::Axis::Horizontal) {
                    child_size.h = m_rect.h - (::acos::i32)(mt + mb);
                    if (child_size.h < 0) child_size.h = 0;
                } else {
                    child_size.w = m_rect.w - (::acos::i32)(ml + mr);
                    if (child_size.w < 0) child_size.w = 0;
                }
            }
            if (cross_offset < 0) cross_offset = 0;

            if (m_axis == ::acos::gui::Axis::Horizontal) {
                child->set_rect({
                    m_rect.x + current_main + ml,
                    m_rect.y + cross_offset + (::acos::i32)mt,
                    child_size.w,
                    child_size.h
                });
                current_main += child_size.w + ml + mr + between_spacing;
            } else {
                child->set_rect({
                    m_rect.x + cross_offset + (::acos::i32)ml,
                    m_rect.y + current_main + mt,
                    child_size.w,
                    child_size.h
                });
                current_main += child_size.h + mt + mb + between_spacing;
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
