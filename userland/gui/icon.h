#pragma once
#include "widget.h"

namespace acos::gui {

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
    Ref<RenderObject> create_render_object() override;
    Icon(IconType type);
    virtual ~Icon();


    void set_color(u32 color) { m_color = color; }
    void set_active(bool active) { m_active = active; }

private:
    IconType m_type;
    u32 m_color;
    bool m_active;

    void draw_terminal(acos::graphics::Renderer* renderer);
    void draw_files(acos::graphics::Renderer* renderer);
    void draw_settings(acos::graphics::Renderer* renderer);
    void draw_code(acos::graphics::Renderer* renderer);
};

} // namespace acos::gui
