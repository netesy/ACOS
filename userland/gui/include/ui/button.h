#pragma once
#include <ui/widget.h>
namespace acos::ui { class Button : public Widget { public:
    Button([[maybe_unused]] const char* text = "") {}
    Ref<LayoutNode> create_layout_node([[maybe_unused]] UIContext* ctx) override { return Ref<LayoutNode>::null(); }
    Ref<RenderObject> create_render_object([[maybe_unused]] UIContext* ctx) override { return Ref<RenderObject>::null(); }
    Button& radius([[maybe_unused]] i32 r) { return *this; }
    Button& background([[maybe_unused]] u32 color) { return *this; }
    template<typename F> Button& on_click([[maybe_unused]] F callback) { return *this; }
}; }
