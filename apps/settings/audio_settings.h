#pragma once
#include <userland/gui/widget.h>
#include <userland/gui/text.h>
#include <userland/gui/listview.h>

namespace acos::apps {

class AudioSettings : public gui::widgets::Panel {
public:
    AudioSettings();
    gui::Ref<gui::RenderObject> create_render_object() override;
    void update_render_object(gui::Ref<gui::RenderObject> render_object) override;

private:
    gui::Ref<gui::widgets::Text> m_title;
    gui::Ref<gui::widgets::ListView> m_device_list;
};

} // namespace acos::apps
