#include "flex.h"
#include "render_object.h"

namespace acos::gui {

class RenderFlex : public RenderObject {
public:
    RenderFlex(Axis axis) : m_axis(axis) {}

    void paint(acos::graphics::Renderer* renderer) override {
        for (auto& child : m_children) {
            if (child) child->paint(renderer);
        }
    }

    void perform_layout(BoxConstraints constraints) override {
        // Layout logic already exists in Flex::layout for now,
        // but it will eventually migrate here.
    }

private:
    Axis m_axis;
};

Ref<RenderObject> Flex::create_render_object() {
    return UIContext::get().region().alloc<RenderFlex>(m_axis);
}

} // namespace acos::gui
