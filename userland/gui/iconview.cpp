#include "iconview.h"
#include "core/context.h"
#include <acos/renderer.h>

namespace acos::gui::widgets {

IconView::IconView() : m_count(0) {
    m_rect = {0, 0, 300, 200};
    for (int i = 0; i < 16; i++) {
        m_icons[i] = {IconType::Terminal, nullptr, nullptr};
    }
}

IconView::~IconView() {}

Ref<RenderObject> IconView::create_render_object() {
    return UIContext::get().region().alloc<RenderIconView>();
}

void IconView::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
}

void IconView::add_icon(IconType type, const char* label, void (*callback)(void*)) {
    if (m_count < 16) {
        m_icons[m_count++] = {type, label, callback};

        auto& region = UIContext::get().region();
        auto icon = region.alloc<Icon>(type);
        icon->on_click(callback);
        add_child(icon.static_cast_to<Widget>());

        set_paint_dirty();
    }
}

RenderIconView::RenderIconView() {}

void RenderIconView::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->fill_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 0xFF181818);
}

void RenderIconView::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;

    // Arrange child icons in a simple grid
    usize idx = 0;
    u32 icon_size = 48;
    u32 spacing = 16;

    for (auto& child : m_children) {
        if (child) {
            u32 cols = m_rect.w / (icon_size + spacing);
            if (cols == 0) cols = 1;

            u32 r = idx / cols;
            u32 c = idx % cols;

            u32 cx = m_rect.x + spacing + c * (icon_size + spacing);
            u32 cy = m_rect.y + spacing + r * (icon_size + spacing);

            child->set_rect({(i32)cx, (i32)cy, (i32)icon_size, (i32)icon_size});
            child->perform_layout(BoxConstraints::tight((i32)icon_size, (i32)icon_size));
            idx++;
        }
    }
}

} // namespace acos::gui::widgets
