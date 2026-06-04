#pragma once
#include "widget.h"
#include "color.h"

namespace acos::ui {

class Text : public Widget {
public:
    Text(const char* value);
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override;
    Ref<RenderObject> create_render_object(UIContext* ctx) override;
    void update_render_object(UIContext* ctx, Ref<RenderObject> obj) override;

    // Explicit override for clarity and to return Text&
    Text& color(u32 c) { Widget::color(c); return *this; }
    Text& font_size(i32 s);
    void set_text(const char* t);
private:
    const char* m_text;
};

} // namespace acos::ui
