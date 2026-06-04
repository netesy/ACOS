#include "button.h"
#include "context.h"
#include "layout_node.h"
#include "render_object.h"
#include "leaf_layout_nodes.h"
#include <kernel/graphics/font.h>

namespace acos::ui {

void ButtonRenderObject::paint([[maybe_unused]] UIContext* ctx, acos::graphics::Renderer* renderer, Position offset) {
    Position pos = { offset.x + m_position.x, offset.y + m_position.y };
    u32 color = pressed ? 0xFF0000AA : background_color;

    if (corner_radius > 0) {
        renderer->fill_rounded_rect(pos.x, pos.y, m_size.w, m_size.h, corner_radius, color);
    } else {
        renderer->fill_rect(pos.x, pos.y, m_size.w, m_size.h, color);
    }

    auto* font = acos::graphics::Font::get_default();
    if (font) {
        u32 tw = 0;
        const char* p = text;
        while (*p++) tw += font->width();

        i32 tx = pos.x + (m_size.w - (i32)tw) / 2;
        i32 ty = pos.y + (m_size.h - (i32)font->height()) / 2;
        renderer->draw_text(text, tx, ty, text_color);
    }
}

void ButtonRenderObject::handle_event([[maybe_unused]] UIContext* ctx, UIEvent& event, EventPhase phase) {
    if (phase == EventPhase::Bubble) {
        if (event.type == EventType::MouseDown) {
            pressed = true;
            event.consume();
        } else if (event.type == EventType::MouseUp) {
            if (pressed) {
                pressed = false;
                event.consume();
            }
        }
    }
}

Button::Button(const char* text) : m_text(text), m_bg_color(Color::Blue), m_radius(4) {}

Ref<LayoutNode> Button::create_layout_node(UIContext* ctx) {
    return ctx->make<LeafLayoutNode>();
}

Ref<RenderObject> Button::create_render_object(UIContext* ctx) {
    return ctx->make<ButtonRenderObject>();
}

void Button::update_render_object(UIContext* ctx, Ref<RenderObject> obj) {
    auto* bro = static_cast<ButtonRenderObject*>(obj.get(ctx));
    bro->background_color = m_bg_color;
    bro->text = m_text;
    bro->corner_radius = m_radius;
}

Button& Button::background(u32 color) { m_bg_color = color; mark_dirty(); return *this; }
Button& Button::radius(i32 r) { m_radius = r; mark_dirty(); return *this; }

Button& Button::on_click(OnClickFn fn, void* data) {
    m_on_click = fn;
    m_on_click_data = data;
    return *this;
}

} // namespace acos::ui
