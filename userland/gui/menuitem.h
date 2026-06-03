#pragma once
#include "widget.h"
#include "signal.h"

namespace acos::gui {

class MenuItem : public Widget {
public:
    MenuItem(const char* label = nullptr);
    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    Signal<> on_triggered;

private:
    const char* m_label;
};

} // namespace acos::gui
