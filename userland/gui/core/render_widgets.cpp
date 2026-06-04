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
        if (!renderer) return;

        // draw_shadow(renderer); - simplified for now
        u32 bg_color = m_style.background_color;
        u8 alpha = 200;

        renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, (bg_color & 0x00FFFFFF) | ((u32)alpha << 24));
        renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, m_style.border_color);

        if (m_label) {
            renderer->draw_text(m_label, m_rect.x + 10, m_rect.y + 8, m_style.foreground_color);
        }
    }
    void perform_layout(BoxConstraints constraints) override {}
    void set_label(const char* label) { m_label = label; }
private:
    const char* m_label = nullptr;
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
