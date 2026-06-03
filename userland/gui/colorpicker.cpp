#include "colorpicker.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ColorPicker::ColorPicker() : m_color(0xFFFFFFFF) {
    m_rect.w = 150;
    m_rect.h = 100;
}

void ColorPicker::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    // Simple grid of colors
    u32 colors[] = {0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFFFFFF00, 0xFFFF00FF, 0xFF00FFFF, 0xFFFFFFFF, 0xFF000000};
    u32 cell_w = m_rect.w / 4;
    u32 cell_h = m_rect.h / 2;

    for (int i = 0; i < 8; i++) {
        u32 x = m_rect.x + (i % 4) * cell_w;
        u32 y = m_rect.y + (i / 4) * cell_h;
        renderer->fill_rect(x, y, cell_w, cell_h, colors[i]);
        if (colors[i] == m_color) {
            renderer->draw_rect(x, y, cell_w, cell_h, 0xFFFFFFFF);
        }
    }
}

void ColorPicker::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        if (pressed && hit_test(mx, my)) {
            u32 colors[] = {0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFFFFFF00, 0xFFFF00FF, 0xFF00FFFF, 0xFFFFFFFF, 0xFF000000};
            u32 cell_w = m_rect.w / 4;
            u32 cell_h = m_rect.h / 2;
            u32 col = (mx - m_rect.x) / cell_w;
            u32 row = (my - m_rect.y) / cell_h;
            u32 idx = row * 4 + col;
            if (idx < 8) {
                m_color = colors[idx];
                on_color_changed.emit(m_color);
            }
        }
    }
}

} // namespace acos::gui
