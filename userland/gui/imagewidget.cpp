#include "imagewidget.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ImageWidget::ImageWidget() : m_data(nullptr), m_img_w(0), m_img_h(0) {}

void ImageWidget::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer || !m_data) return;

    for (u32 y = 0; y < m_img_h; y++) {
        if (m_rect.y + (i32)y >= 1080) break;
        for (u32 x = 0; x < m_img_w; x++) {
            if (m_rect.x + (i32)x >= 1920) break;
            renderer->draw_pixel(m_rect.x + x, m_rect.y + y, m_data[y * m_img_w + x]);
        }
    }
}

} // namespace acos::gui
