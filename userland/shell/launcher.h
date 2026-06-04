#pragma once
#include "widget.h"
#include "basic_widgets.h"

namespace acos::shell {

class Launcher : public ui::Widget {
public:
    Launcher();
    ui::Ref<ui::LayoutNode> create_layout_node(ui::UIContext* ctx) override;
    ui::Ref<ui::RenderObject> create_render_object(ui::UIContext* ctx) override;
};

} // namespace acos::shell
