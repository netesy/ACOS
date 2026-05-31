#pragma once
#include <userland/gui/widget.h>

namespace acos::shell {

class Launcher : public gui::Widget {
public:
    Launcher();
    void draw(u32* buffer, u32 pitch) override;
    void show();
    void hide();

private:
    bool m_active;
};

} // namespace acos::shell
