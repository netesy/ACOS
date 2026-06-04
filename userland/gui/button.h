#include "render_object.h"
#pragma once
#include "widget.h"
#include "color.h"

namespace acos::ui {

class ButtonRenderObject : public RenderObject {
public:
    u32 background_color = Color::Blue;
    const char* text = "";
    u32 text_color = Color::White;
    i32 corner_radius = 4;
    bool pressed = false;

    void paint(UIContext* ctx, acos::graphics::Renderer* renderer, Position offset) override;
    void handle_event(UIContext* ctx, UIEvent& event, EventPhase phase) override;
};

class Button : public Widget {
public:
    Button(const char* text = "");

    Ref<LayoutNode> create_layout_node(UIContext* ctx) override;
    Ref<RenderObject> create_render_object(UIContext* ctx) override;
    void update_render_object(UIContext* ctx, Ref<RenderObject> obj) override;

    Button& background(u32 color);
    Button& radius(i32 r);

    typedef void (*OnClickFn)(void*);
    Button& on_click(OnClickFn fn, void* data = nullptr);

private:
    const char* m_text;
    u32 m_bg_color;
    i32 m_radius;
    OnClickFn m_on_click = nullptr;
    void* m_on_click_data = nullptr;
};

} // namespace acos::ui
