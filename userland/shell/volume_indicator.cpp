#include "volume_indicator.h"
#include <userland/gui/theme.h>
#include <userland/gui/core/render_widgets.h>
#include <userland/gui/core/context.h>

namespace acos::shell {

class RenderVolumeIndicator : public gui::widgets::RenderObject {
public:
    RenderVolumeIndicator() : m_volume(50) {}
    void paint(acos::graphics::Renderer* renderer) override {
        if (!renderer) return;
        const u32 x = static_cast<u32>(m_rect.x);
        const u32 y = static_cast<u32>(m_rect.y);
        const u32 h = static_cast<u32>(m_rect.h);
        const u32 bar_width = (m_volume > 100 ? 100 : m_volume) / 4;

        renderer->draw_rect(x, y + 8, 8, 14, gui::g_current_theme.text);
        renderer->fill_rect(x + 10, y + 6, bar_width, h - 12, gui::g_current_theme.primary);
        renderer->draw_border(x + 10, y + 6, 25, h - 12, gui::g_current_theme.border, 1);
    }
    void perform_layout(gui::BoxConstraints constraints) override { (void)constraints; }
    void set_volume(u32 vol) { m_volume = vol; }
private:
    u32 m_volume;
};

VolumeIndicator::VolumeIndicator() : m_volume(50) {
    m_rect = {750, 5, 40, 30};
}

void VolumeIndicator::draw(acos::graphics::Renderer* renderer) {
    (void)renderer;
}

gui::Ref<gui::RenderObject> VolumeIndicator::create_render_object() {
    return gui::UIContext::get().region().alloc<RenderVolumeIndicator>();
}

void VolumeIndicator::update_render_object(gui::Ref<gui::RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rv = static_cast<RenderVolumeIndicator*>(render_object.operator->());
    if (rv) {
        rv->set_volume(m_volume);
    }
}

} // namespace acos::shell
