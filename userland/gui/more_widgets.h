#pragma once
#include "widget.h"
#include "basic_widgets.h"

namespace acos::ui {

class TextBox : public Widget { public:
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<LeafLayoutNode>(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
};
class ListView : public Widget { public:
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<LeafLayoutNode>(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
    void clear() {}
    void add_item([[maybe_unused]] const char* s) {}
};
class ProgressBar : public Widget { public:
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<LeafLayoutNode>(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
    void set_value([[maybe_unused]] float v) {}
};
class TextArea : public Widget { public:
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<LeafLayoutNode>(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
    void set_text([[maybe_unused]] const char* s) {}
};
class Slider : public Widget { public:
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<LeafLayoutNode>(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
    void set_value([[maybe_unused]] float v) {}
};
class ComboBox : public Widget { public:
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<LeafLayoutNode>(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
    void add_item([[maybe_unused]] const char* s) {}
};
class Switch : public Widget { public:
    Switch([[maybe_unused]] const char* s) {}
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<LeafLayoutNode>(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
    void set_on([[maybe_unused]] bool on) {}
};
class TabWidget : public Widget { public:
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<LeafLayoutNode>(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
    void add_tab([[maybe_unused]] const char* s, [[maybe_unused]] Widget* w) {}
};
class Panel : public Widget { public:
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<LeafLayoutNode>(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
};
class Icon : public Widget { public:
    Ref<LayoutNode> create_layout_node(UIContext* ctx) override { return ctx->make<LeafLayoutNode>(); }
    Ref<RenderObject> create_render_object(UIContext* ctx) override { return ctx->make<ContainerRenderObject>(); }
};

} // namespace acos::ui
