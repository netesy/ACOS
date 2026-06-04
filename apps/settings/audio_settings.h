#pragma once
#include "widget.h"
#include "label.h"
#include "listview.h"
#include <kernel/graphics/renderer.h>

namespace acos::apps {

class AudioSettings : public ui::Widget {
public:
    AudioSettings();
    void draw(acos::graphics::Renderer* renderer);

    ui::Ref<ui::LayoutNode> create_layout_node(ui::UIContext* ctx) override;
    ui::Ref<ui::RenderObject> create_render_object(ui::UIContext* ctx) override;

private:
    ui::Label m_title;
    ui::ListView m_device_list;
};

} // namespace acos::apps
