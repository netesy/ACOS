#pragma once
#include <ui/widget.h>
namespace acos::ui { class Switch : public Widget { public:
    Switch([[maybe_unused]] const char* label = "") {}
    Ref<LayoutNode> create_layout_node([[maybe_unused]] UIContext* ctx) override { return Ref<LayoutNode>::null(); }
    Ref<RenderObject> create_render_object([[maybe_unused]] UIContext* ctx) override { return Ref<RenderObject>::null(); }
    void set_on([[maybe_unused]] bool on) {}
}; }
