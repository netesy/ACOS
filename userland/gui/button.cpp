#include "button.h"
#include "context.h"
#include "render_object.h"
#include "leaf_layout_nodes.h"

namespace acos::ui {

class ButtonRenderObject : public RenderObject {
public:
    u32 background_color = Color::Blue;
    void paint([[maybe_unused]] UIContext* ctx, acos::graphics::Renderer* renderer, Position offset) override {
        Position pos = { offset.x + m_position.x, offset.y + m_position.y };
        renderer->draw_rect(pos.x, pos.y, m_size.w, m_size.h, background_color);
    }
};

Button::Button(const char* text) : m_bg_color(Color::Blue) { (void)text; }
Ref<LayoutNode> Button::create_layout_node(UIContext* ctx) { return ctx->make<LeafLayoutNode>(); }
Ref<RenderObject> Button::create_render_object(UIContext* ctx) { return ctx->make<ButtonRenderObject>(); }
void Button::update_render_object(UIContext* ctx, Ref<RenderObject> obj) {
    static_cast<ButtonRenderObject*>(obj.get(ctx))->background_color = m_bg_color;
}
Button& Button::background(u32 color) { m_bg_color = color; mark_dirty(); return *this; }

} // namespace acos::ui
