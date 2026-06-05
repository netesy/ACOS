#pragma once
#include <userland/gui/widget.h>
#include <userland/gui/core/flex.h>
#include "volume_indicator.h"

namespace acos::shell {

class Taskbar : public gui::widgets::Panel {
public:
    Taskbar();
    void update_clock();

    gui::Ref<gui::RenderObject> create_render_object() override;
    void update_render_object(gui::Ref<gui::RenderObject> render_object) override;

private:
    char m_clock_str[16];
    VolumeIndicator m_volume;
};

} // namespace acos::shell
