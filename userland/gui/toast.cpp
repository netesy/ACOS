#include "toast.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

Toast::Toast(const char* message) : m_message(message), m_timer(0), m_duration(0), m_alpha(0) {
    m_rect = {300, 500, 200, 40};
    set_visible(false);
}

void Toast::show(u32 duration_ms) {
    m_duration = duration_ms;
    m_timer = 0;
    m_alpha = 255;
    set_visible(true);
}

void Toast::update(u64 delta_ms) {
    if (!is_visible()) return;
    m_timer += delta_ms;
    if (m_timer > m_duration) {
        set_visible(false);
    } else if (m_timer > m_duration - 500) {
        // Fade out
        m_alpha = (u8)(255 * (m_duration - m_timer) / 500);
    }
}


Ref<RenderObject> Toast::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
