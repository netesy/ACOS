#include <acos/process.h>
#include <acos/runtime.h>
#include "volume_indicator.h"
#include <userland/gui/core/render_object.h>
#include <userland/gui/core/context.h>

namespace acos::shell {

class RenderVolumeIndicator : public gui::RenderObject {
public:
    RenderVolumeIndicator() : m_volume(0) {}
    void paint(acos::graphics::Renderer* renderer) override {
        if (!renderer) return;
        const u32 x = static_cast<u32>(m_rect.x);
        const u32 y = static_cast<u32>(m_rect.y);
        const u32 w = static_cast<u32>(m_rect.w);
        const u32 h = static_cast<u32>(m_rect.h);

        renderer->draw_rect(x, y, w, h, 0xFF444444);
        u32 vol_w = (w * m_volume) / 100;
        renderer->draw_rect(x, y, vol_w, h, 0xFF00FF00);
    }
    void perform_layout(gui::BoxConstraints constraints) override {
        m_rect.w = constraints.constrain({100, 20}).w;
        m_rect.h = constraints.constrain({100, 20}).h;
    }
    void set_volume(u32 vol) { m_volume = vol; }
private:
    u32 m_volume;
};

VolumeIndicator::VolumeIndicator() : m_volume(50) {
    m_rect = {0, 0, 100, 20};
}

VolumeIndicator::~VolumeIndicator() {}

gui::Ref<gui::RenderObject> VolumeIndicator::create_render_object() {
    return gui::UIContext::get().region().alloc<RenderVolumeIndicator>();
}

void VolumeIndicator::update_render_object(gui::Ref<gui::RenderObject> render_object) {
    gui::Widget::update_render_object(render_object);
    auto rv = static_cast<RenderVolumeIndicator*>(render_object.operator->());
    rv->set_volume(m_volume);
}

} // namespace acos::shell
