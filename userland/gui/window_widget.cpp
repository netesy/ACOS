#include <acos/process.h>
#include <acos/runtime.h>
#include "window_widget.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"
#include "widgets/fluent.h"

namespace acos::gui {

WindowWidget::WindowWidget(const char* title, i32 x, i32 y, i32 w, i32 h)
    : m_title(title), m_window_handle(0) {
    m_rect = {x, y, w, h};

    auto& region = UIContext::get().region();

    auto root = region.alloc<widgets::Column>();
    root->spacing(0);

    auto title_bar = region.alloc<widgets::Panel>();
    title_bar->set_rect({0, 0, w, 28});
    title_bar->set_background_color(0xFF2A2A2B);
    title_bar->radius(4);

    auto title_text = region.alloc<widgets::Text>(title);
    title_text->set_rect({10, 0, w - 20, 28});
    title_bar->add_child(title_text.static_cast_to<Widget>());

    root->add_child(title_bar.static_cast_to<Widget>());

    auto content = region.alloc<widgets::Panel>();
    content->set_rect({0, 0, w, h - 28});
    content->set_background_color(0xFF1A1A1B);
    content->radius(0);
    m_content_panel = content.static_cast_to<Widget>();
    root->add_child(m_content_panel);

    Widget::add_child(root.static_cast_to<Widget>());
}

WindowWidget::~WindowWidget() {}

Ref<RenderObject> WindowWidget::create_render_object() {
    auto rp = UIContext::get().region().alloc<widgets::RenderPanel>();
    rp->set_glass(true);
    return rp.static_cast_to<RenderObject>();
}

void WindowWidget::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
}

void WindowWidget::add_child(Ref<Widget> child) {
    if (m_content_panel) {
        m_content_panel->add_child(child);
    } else {
        Widget::add_child(child);
    }
}

void WindowWidget::show() {
    set_visible(true);
}

} // namespace acos::gui
