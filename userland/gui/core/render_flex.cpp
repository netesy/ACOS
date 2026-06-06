#include "flex.h"
#include "render_object.h"
#include "context.h"

namespace acos::gui::widgets {

class RenderFlex : public RenderObject {
public:
    RenderFlex(::acos::gui::Axis axis) : m_axis(axis) {}

    void paint(::acos::graphics::Renderer* renderer) override {
        for (auto& child : m_children) {
            if (child) child->paint(renderer);
        }
    }

    void perform_layout(BoxConstraints constraints) override {
        ::acos::i32 main_total = 0;
        ::acos::i32 cross_max = 0;

        for (auto& child : m_children) {
            if (!child) continue;

            BoxConstraints child_constraints;
            if (m_axis == ::acos::gui::Axis::Horizontal) {
                child_constraints = BoxConstraints::loose(constraints.max_w - main_total, constraints.max_h);
            } else {
                child_constraints = BoxConstraints::loose(constraints.max_w, constraints.max_h - main_total);
            }

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

        Size self_size = constraints.constrain(m_axis == ::acos::gui::Axis::Horizontal ? Size{main_total, cross_max} : Size{cross_max, main_total});
        m_rect.w = self_size.w;
        m_rect.h = self_size.h;

        ::acos::i32 current_main = 0;
        for (auto& child : m_children) {
            if (!child) continue;
            Size child_size = {child->rect().w, child->rect().h};
            if (m_axis == ::acos::gui::Axis::Horizontal) {
                child->set_rect({m_rect.x + current_main, m_rect.y, child_size.w, child_size.h});
                current_main += child_size.w;
            } else {
                child->set_rect({m_rect.x, m_rect.y + current_main, child_size.w, child_size.h});
                current_main += child_size.h;
            }
        }
    }

private:
    ::acos::gui::Axis m_axis;
};

Ref<RenderObject> Flex::create_render_object() {
    return UIContext::get().region().alloc<RenderFlex>(m_axis);
}

} // namespace acos::gui::widgets
