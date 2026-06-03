#pragma once
#include <ui/widget.h>
#include <ui/color.h>

namespace acos::ui {

class Text : public Widget {
public:
    Text(const char* value) {}
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return Ref<LayoutNode>::null(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return Ref<RenderObject>::null(); }

    Text& font_size(i32 size) { return *this; }
    Text& color(u32 c) { return *this; }
};

} // namespace acos::ui
