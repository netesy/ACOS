#pragma once
#include <ui/widget.h>
namespace acos::ui { class TabWidget : public Widget { public:
    Ref<LayoutNode> create_layout_node([[maybe_unused]] UIContext* ctx) override { return Ref<LayoutNode>::null(); }
    Ref<RenderObject> create_render_object([[maybe_unused]] UIContext* ctx) override { return Ref<RenderObject>::null(); }
    void add_tab([[maybe_unused]] const char* name, [[maybe_unused]] Widget* content) {}
}; }
