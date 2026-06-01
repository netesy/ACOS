#pragma once
#include <userland/gui/widget.h>
#include "volume_indicator.h"

namespace acos::shell {

class Taskbar : public gui::Widget {
public:
    Taskbar();
    void draw(acos::graphics::Renderer* renderer) override;
    void update_clock();

private:
    char m_clock_str[16];
    VolumeIndicator* m_volume;
};

} // namespace acos::shell
