#pragma once
#include <userland/gui/widget.h>

namespace acos::shell {

class Taskbar : public gui::Widget {
public:
    Taskbar();
    void draw(u32* buffer, u32 pitch) override;
    void update_clock();

private:
    char m_clock_str[16];
};

} // namespace acos::shell
