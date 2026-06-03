#pragma once
#include <ui/widget.h>
#include <ui/label.h>
#include <ui/listview.h>
#include "kernel/graphics/renderer.h"

namespace acos::apps {

class AudioSettings : public ui::Widget {
public:
    AudioSettings();
    void draw(acos::graphics::Renderer* renderer);

    ui::Ref<ui::LayoutNode> create_layout_node([[maybe_unused]] ui::UIContext* ctx) override { return ui::Ref<ui::LayoutNode>::null(); }
    ui::Ref<ui::RenderObject> create_render_object([[maybe_unused]] ui::UIContext* ctx) override { return ui::Ref<ui::RenderObject>::null(); }

private:
    ui::Label m_title;
    ui::ListView m_device_list;
};

} // namespace acos::apps
