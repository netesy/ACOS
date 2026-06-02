#pragma once
#include "widget.h"

namespace acos::gui {

class Slider : public Widget {
public:
    Slider();
    virtual ~Slider();

    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    float value() const { return m_value; }
    void set_value(float value);
    void set_range(float min, float max);

private:
    float m_value;
    float m_min;
    float m_max;
    bool m_dragging;
};

} // namespace acos::gui
