#pragma once
#include <userland/gui/widget.h>

namespace acos::shell {

class Launcher : public gui::Widget {
public:
    Launcher();
    void draw(acos::graphics::Renderer* renderer) override;
    void show();
    void hide();

private:
    bool m_active;
};

} // namespace acos::shell
