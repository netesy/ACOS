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
        auto* font = acos::graphics::Font::get_default();
        i32 tw = 0, th = 16;
        if (font) {
            th = font->height();
            const char* p = m_text;
            if (p) while (*p++) tw += font->width();
        } else {
            i32 len = 0; if (m_text) while (m_text[len]) len++;
            tw = len * 8;
        }
        m_size = constraints.satisfy({ tw, th });
        return m_size;
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

Text::Text(const char* value) : m_text(value) {}
Ref<LayoutNode> Text::create_layout_node(UIContext* ctx) { return ctx->make<TextLayoutNode>(m_text); }
Ref<RenderObject> Text::create_render_object(UIContext* ctx) { return ctx->make<TextRenderObject>(); }

void Text::update_render_object(UIContext* ctx, Ref<RenderObject> obj) {
    auto* tro = static_cast<TextRenderObject*>(obj.get(ctx));
    tro->text = m_text;
    tro->color = m_style.text_color;
}

Text& Text::font_size([[maybe_unused]] i32 s) { m_style.font_size = s; mark_dirty(); return *this; }
void Text::set_text(const char* t) { m_text = t; mark_dirty(); }

} // namespace acos::ui
