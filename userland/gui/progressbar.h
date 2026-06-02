#pragma once
#include "widget.h"

namespace acos::gui {

class ProgressBar : public Widget {
public:
    ProgressBar();
    virtual ~ProgressBar();

    void draw(acos::graphics::Renderer* renderer) override;

    void set_value(float value);
    float value() const { return m_value; }

    void set_range(float min, float max);

private:
    float m_value;
    float m_min;
    float m_max;
};

} // namespace acos::gui
