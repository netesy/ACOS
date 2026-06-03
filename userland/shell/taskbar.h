#pragma once
#include <ui/widget.h>
#include <ui/basic_widgets.h>

namespace acos::shell {

class Taskbar : public ui::Widget {
public:
    Taskbar();

    ui::Ref<ui::LayoutNode> create_layout_node(ui::UIContext* ctx) override;
    ui::Ref<ui::RenderObject> create_render_object(ui::UIContext* ctx) override;

    void update_clock();

private:
    char m_clock_str[16];
};

} // namespace acos::shell
