#include "text.h"
#include "context.h"
#include "layout_node.h"
#include "render_object.h"
#include "leaf_layout_nodes.h"
#include <kernel/graphics/font.h>

namespace acos::ui {

class TextLayoutNode : public LayoutNode {
public:
    TextLayoutNode(const char* t) : m_text(t) {}
    Size perform_layout([[maybe_unused]] UIContext* ctx, Constraints constraints) override {
        i32 len = 0; if (m_text) while (m_text[len]) len++;
        m_size = constraints.satisfy({ len * 8, 16 }); return m_size;
    }
private:
    const char* m_text;
};

class TextRenderObject : public RenderObject {
public:
    const char* text = ""; u32 color = Color::White;
    void paint([[maybe_unused]] UIContext* ctx, acos::graphics::Renderer* renderer, Position offset) override {
        Position pos = { offset.x + m_position.x, offset.y + m_position.y };
        renderer->draw_text(text, pos.x, pos.y, color);
    }
};

Text::Text(const char* value) : m_text(value), m_color(Color::White) {}
Ref<LayoutNode> Text::create_layout_node(UIContext* ctx) { return ctx->make<TextLayoutNode>(m_text); }
Ref<RenderObject> Text::create_render_object(UIContext* ctx) { return ctx->make<TextRenderObject>(); }
void Text::update_render_object(UIContext* ctx, Ref<RenderObject> obj) {
    auto* tro = static_cast<TextRenderObject*>(obj.get(ctx));
    tro->text = m_text; tro->color = m_color;
}
Text& Text::color(u32 c) { m_color = c; mark_dirty(); return *this; }
Text& Text::font_size([[maybe_unused]] i32 s) { mark_dirty(); return *this; }
void Text::set_text(const char* t) { m_text = t; mark_dirty(); }

} // namespace acos::ui
