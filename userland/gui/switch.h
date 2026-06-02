#pragma once
#include "widget.h"

namespace acos::gui {

class Switch : public Widget {
public:
    Switch(const char* label = nullptr);
    virtual ~Switch();

    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    bool on() const { return m_on; }
    void set_on(bool on) { m_on = on; }

private:
    const char* m_label;
    bool m_on;
};

} // namespace acos::gui
