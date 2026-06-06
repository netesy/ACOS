#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class Button : public Widget {
public:
    Button(const char* label = nullptr);
    virtual ~Button();

    void update(::acos::u64 delta_ms) override;
    void on_event(Event& event) override;

    void set_on_click(void (*callback)(void*)) {
        m_on_click = callback;
    }

    const char* label() const { return m_label; }
    void set_label(const char* label) { m_label = label; }

    // Internal Fluent API
    Button& label(const char* l) { set_label(l); return *this; }
    Button& on_click(void (*callback)(void*)) { m_on_click = callback; return *this; }

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;

private:
    const char* m_label;
    bool m_mouse_over;
    void (*m_on_click)(void*) = nullptr;
};

} // namespace acos::gui::widgets
