#include "audio_settings.h"
#include <userland/gui/panel.h>
#include <userland/gui/theme.h>
#include <userland/gui/core/context.h>

namespace acos::apps {

AudioSettings::AudioSettings() {
    m_rect = {0, 0, 400, 300};
    auto& region = gui::UIContext::get().region();

    m_title = region.alloc<gui::widgets::Text>("Audio Settings");
    m_title->set_position(10, 10);
    add_child(m_title.static_cast_to<gui::Widget>());

    m_device_list = region.alloc<gui::widgets::ListView>();
    m_device_list->set_rect({10, 40, 380, 240});
    m_device_list->add_item("VirtIO Sound Card");
    m_device_list->add_item("Built-in Speaker");
    add_child(m_device_list.static_cast_to<gui::Widget>());
}

gui::Ref<gui::RenderObject> AudioSettings::create_render_object() {
    return gui::widgets::Panel::create_render_object();
}

void AudioSettings::update_render_object(gui::Ref<gui::RenderObject> render_object) {
    gui::widgets::Panel::update_render_object(render_object);
}

} // namespace acos::apps
