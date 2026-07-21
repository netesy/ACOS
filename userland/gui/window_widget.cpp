#include <acos/process.h>
#include <acos/runtime.h>
#include "window_widget.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"
#include "widgets/fluent.h"

namespace acos::gui {

class WindowTitleBar : public widgets::Panel {
public:
    WindowTitleBar(WindowWidget* window) : m_window(window), m_dragging(false), m_last_x(0), m_last_y(0) {}

    void on_event(Event& event) override {
        const auto& raw = event.raw;
        if (raw.type == ::acos::abi::InputType::Mouse) {
            i32 mx = event.mouse_x;
            i32 my = event.mouse_y;
            bool pressed = (raw.value & 0x01) != 0;

            if (pressed) {
                if (!m_dragging) {
                    m_dragging = true;
                    m_last_x = mx;
                    m_last_y = my;

                    // Bring to front
                    Ref<Widget> win_ref = m_window->self();
                    Ref<Widget> parent = win_ref->parent();
                    if (parent) {
                        parent->remove_child(win_ref);
                        parent->add_child(win_ref);
                        UIContext::get().focus_manager().set_focus(win_ref);
                    }
                } else {
                    i32 dx = mx - m_last_x;
                    i32 dy = my - m_last_y;
                    if (dx != 0 || dy != 0) {
                        Rect r = m_window->rect();
                        r.x += dx;
                        r.y += dy;
                        m_window->set_rect(r);
                        m_last_x = mx;
                        m_last_y = my;
                        m_window->set_layout_dirty();
                    }
                }
                event.stop_propagation();
            } else {
                m_dragging = false;
            }
        }
    }

private:
    WindowWidget* m_window;
    bool m_dragging;
    i32 m_last_x;
    i32 m_last_y;
};

class CloseButton : public Widget {
public:
    CloseButton(WindowWidget* window) : m_window(window), m_hovered(false) {
        i32 w = window->rect().w;
        set_rect({w - 24, 4, 20, 20});
    }

    Ref<RenderObject> create_render_object() override {
        return UIContext::get().region().alloc<widgets::RenderButton>();
    }

    void update_render_object(Ref<RenderObject> render_object) override {
        Widget::update_render_object(render_object);
        auto rb = static_cast<widgets::RenderButton*>(render_object.operator->());
        if (rb) {
            rb->set_label("X");
            rb->set_hovered(m_hovered);
            rb->set_pressed(m_state == WidgetState::Pressed);
        }
    }

    void on_event(Event& event) override {
        const auto& raw = event.raw;
        if (raw.type == ::acos::abi::InputType::Mouse) {
            i32 mx = event.mouse_x;
            i32 my = event.mouse_y;
            bool pressed = (raw.value & 0x01) != 0;

            if (m_rect.contains(mx, my)) {
                m_hovered = true;
                if (pressed) {
                    m_state = WidgetState::Pressed;
                } else {
                    if (m_state == WidgetState::Pressed) {
                        Ref<Widget> win_ref = m_window->self();
                        Ref<Widget> parent = win_ref->parent();
                        if (parent) {
                            parent->remove_child(win_ref);
                            parent->set_layout_dirty();
                        }
                    }
                    m_state = WidgetState::Hovered;
                }
            } else {
                m_hovered = false;
                m_state = WidgetState::Normal;
            }
            set_paint_dirty();
            event.stop_propagation();
        }
    }

private:
    WindowWidget* m_window;
    bool m_hovered;
};

WindowWidget::WindowWidget(const char* title, i32 x, i32 y, i32 w, i32 h)
    : m_title(title), m_window_handle(0) {
    m_rect = {x, y, w, h};

    auto& region = UIContext::get().region();

    auto root = region.alloc<widgets::Column>();
    root->spacing(0);

    auto title_bar = region.alloc<WindowTitleBar>(this);
    title_bar->set_rect({0, 0, w, 28});
    title_bar->set_background_color(0xFF2A2A2B);
    title_bar->radius(4);

    auto title_text = region.alloc<widgets::Text>(title);
    title_text->set_rect({10, 0, w - 40, 28});
    title_bar->add_child(title_text.static_cast_to<Widget>());

    auto close_btn = region.alloc<CloseButton>(this);
    title_bar->add_child(close_btn.static_cast_to<Widget>());

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
