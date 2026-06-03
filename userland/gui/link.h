#pragma once
#include "label.h"
#include "signal.h"

namespace acos::gui {

class Link : public Label {
public:
    Link(const char* text);
    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    Signal<> on_clicked;
};

} // namespace acos::gui
