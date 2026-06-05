#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class Slider : public Widget {
public:
    Slider();
    virtual ~Slider();

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;
    void on_event(Event& event) override;

    float value() const { return m_value; }
    void set_value(float value);
    void set_range(float min, float max);

    // Internal Fluent API
    Slider& value(float v) { set_value(v); return *this; }
    Slider& range(float min, float max) { set_range(min, max); return *this; }

private:
    float m_value;
    float m_min;
    float m_max;
    bool m_dragging;
};

} // namespace acos::gui::widgets
