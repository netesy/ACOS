#pragma once
#include <ui/widget.h>
namespace acos::ui { class TextBox : public Widget { public:
    Ref<LayoutNode> create_layout_node([[maybe_unused]] UIContext* ctx) override { return Ref<LayoutNode>::null(); }
    Ref<RenderObject> create_render_object([[maybe_unused]] UIContext* ctx) override { return Ref<RenderObject>::null(); }
}; }
