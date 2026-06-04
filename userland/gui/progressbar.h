#pragma once
#include "widget.h"

namespace acos::gui {

class ProgressBar : public Widget {
public:
    ProgressBar();
    virtual ~ProgressBar();

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;

    void set_value(float value);
    float value() const { return m_value; }

    void set_range(float min, float max);

    // Fluent API
    ProgressBar& value(float v) { set_value(v); return *this; }
    ProgressBar& range(float min, float max) { set_range(min, max); return *this; }

private:
    float m_value;
    float m_min;
    float m_max;
};

} // namespace acos::gui
