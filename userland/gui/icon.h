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

    void set_color(::acos::u32 color) { m_color = color; }
    void set_active(bool active) { m_active = active; }

private:
    IconType m_type;
    ::acos::u32 m_color;
    bool m_active;
};

} // namespace acos::gui::widgets
