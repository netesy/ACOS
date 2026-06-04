#include "../button.h"
#include "../label.h"
#include "render_object.h"
#include "context.h"
#include "stack.h"
#include "grid.h"

namespace acos::gui {

class RenderButton : public RenderObject {
public:
    void paint(acos::graphics::Renderer* renderer) override {
        // Drawing logic will eventually move here from Button::draw
    }
    void perform_layout(BoxConstraints constraints) override {}
};

class RenderLabel : public RenderObject {
public:
    void paint(acos::graphics::Renderer* renderer) override {
        // Drawing logic will eventually move here from Label::draw
    }
    void perform_layout(BoxConstraints constraints) override {}
};

Ref<RenderObject> Button::create_render_object() {
    return UIContext::get().region().alloc<RenderButton>();
}

Ref<RenderObject> Label::create_render_object() {
    return UIContext::get().region().alloc<RenderLabel>();
}

class RenderStack : public RenderObject {
public:
    void paint(acos::graphics::Renderer* renderer) override {
        for (auto& child : m_children) if (child) child->paint(renderer);
    }
    void perform_layout(BoxConstraints constraints) override {}
};

class RenderGrid : public RenderObject {
public:
    void paint(acos::graphics::Renderer* renderer) override {
        for (auto& child : m_children) if (child) child->paint(renderer);
    }
    void perform_layout(BoxConstraints constraints) override {}
};

Ref<RenderObject> Stack::create_render_object() {
    return UIContext::get().region().alloc<RenderStack>();
}

Ref<RenderObject> Grid::create_render_object() {
    return UIContext::get().region().alloc<RenderGrid>();
}

} // namespace acos::gui
