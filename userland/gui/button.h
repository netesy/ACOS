#pragma once
#include "widget.h"
#include "color.h"

namespace acos::ui {

class Button : public Widget {
public:
    Button(const char* text = "");
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override;
    Ref<RenderObject> create_render_object(UIContext* ctx) override;
    void update_render_object(UIContext* ctx, Ref<RenderObject> obj) override;
    Button& background(u32 color);
    template<typename F> Button& on_click([[maybe_unused]] F callback) { return *this; }
private:
    u32 m_bg_color;
};

} // namespace acos::ui
