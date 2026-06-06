#pragma once
#include <userland/gui/widget.h>

namespace acos::shell {

class VolumeIndicator : public gui::Widget {
public:
    VolumeIndicator();
    virtual ~VolumeIndicator();
    gui::Ref<gui::RenderObject> create_render_object() override;
    void update_render_object(gui::Ref<gui::RenderObject> render_object) override;
    void set_volume(u32 vol) { m_volume = vol; }

private:
    u32 m_volume;
};

} // namespace acos::shell
