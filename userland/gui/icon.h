#pragma once
#include "widget.h"

namespace acos::gui::widgets {

enum class IconType {
    Terminal,
    Files,
    Settings,
    Code,
    Monitor,
    Speaker,
    Network,
    Battery
};

class Icon : public Widget {
public:
    Icon(IconType type);
    virtual ~Icon();

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;
    void on_event(Event& event) override;

    void set_color(::acos::u32 color) { m_color = color; }
    void set_active(bool active) { m_active = active; }
    void set_background_color(::acos::u32 color) { m_style.background_color = color; set_paint_dirty(); }
    void set_size(::acos::i32 size) { m_rect.w = size; m_rect.h = size; set_layout_dirty(); }
    void on_click(void (*callback)(void*)) { m_on_click = callback; }

private:
    IconType m_type;
    ::acos::u32 m_color;
    bool m_active;
    void (*m_on_click)(void*);
};

} // namespace acos::gui::widgets
