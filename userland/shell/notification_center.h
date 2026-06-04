#pragma once
#include "widget.h"
#include "basic_widgets.h"

namespace acos::shell {

class NotificationCenter : public ui::Widget {
public:
    NotificationCenter();
    ui::Ref<ui::LayoutNode> create_layout_node(ui::UIContext* ctx) override;
    ui::Ref<ui::RenderObject> create_render_object(ui::UIContext* ctx) override;
};

} // namespace acos::shell
