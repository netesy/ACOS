#pragma once
#include "widget.h"
#include "color.h"

namespace acos::ui {

class TextLayoutNode;
class TextRenderObject;

class Text : public Widget {
public:
    Text(const char* value);
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override;
    Ref<RenderObject> create_render_object(UIContext* ctx) override;
    void update_render_object(UIContext* ctx, Ref<RenderObject> obj) override;
    Text& color(u32 c);
    Text& font_size(i32 s);
    void set_text(const char* t);
private:
    const char* m_text; u32 m_color;
};

} // namespace acos::ui
