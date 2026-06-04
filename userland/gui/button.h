#pragma once
#include "widget.h"
#include "signal.h"

namespace acos::gui {

class Button : public Widget {
public:
    Button(const char* label = nullptr);
    virtual ~Button();

    void update(u64 delta_ms) override;

    void set_on_click(void (*callback)(void*), void* receiver) {
        m_on_click_signal.connect(receiver, (Signal<>::Slot)callback);
    }

    const char* label() const { return m_label; }
    void set_label(const char* label) { m_label = label; }

    // Fluent API
    Button& label(const char* l) { set_label(l); return *this; }
    Button& on_click(void (*callback)(void*)) { m_on_click = callback; return *this; }

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;

private:
    const char* m_label;
    u32 m_bg_color;
    u32 m_text_color;
    u32 m_hover_color;
    u32 m_pressed_color;

    bool m_mouse_over;
    u64 m_press_time;

    void (*m_on_click)(void*) = nullptr;
};

} // namespace acos::gui
