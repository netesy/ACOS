#include "shortcut_widget.h"
#include "desktop_shell.h"
#include <userland/gui/core/render_widgets.h>
#include <userland/gui/core/context.h>
#include <userland/gui/theme.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::shell {

class RenderShortcut : public gui::RenderObject {
public:
    RenderShortcut() : m_name(nullptr), m_icon(gui::widgets::IconType::Files), m_hovered(false), m_pressed(false) {}

    void paint(::acos::graphics::Renderer* renderer) override {
        if (!renderer) return;

        if (m_pressed) {
            renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 8, 0x66000000);
            renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 8, 0xFFFFFFFF);
        } else if (m_hovered) {
            renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 8, 0x33000000);
            renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 8, 0x88FFFFFF);
        }

        // Draw Icon
        u32 icon_size = 48;
        u32 ix = m_rect.x + (m_rect.w - icon_size) / 2;
        u32 iy = m_rect.y + 12;

        // Render a high-fidelity icon base
        renderer->fill_rounded_rect(ix, iy, icon_size, icon_size, 12, 0xFF2A2A2B);
        renderer->draw_rounded_rect(ix, iy, icon_size, icon_size, 12, 0xFF4A4A4B);

        // Draw icon symbol based on type
        u32 symbol_color = 0xFFFFFFFF;
        switch (m_icon) {
            case gui::widgets::IconType::Terminal:
                renderer->draw_text(">_", ix + 12, iy + 16, symbol_color);
                break;
            case gui::widgets::IconType::Files:
                renderer->fill_rect(ix + 10, iy + 14, 28, 20, symbol_color);
                break;
            default:
                renderer->draw_rect(ix + 14, iy + 14, 20, 20, symbol_color);
                break;
        }

        if (m_name) {
            u32 lw, lh;
            renderer->measure_text(m_name, lw, lh);

            // Background for text to improve readability against wallpaper
            u32 tx = m_rect.x + (m_rect.w - lw) / 2;
            u32 ty = iy + icon_size + 12;

            renderer->fill_rounded_rect(tx - 4, ty - 2, lw + 8, lh + 4, 4, 0x88000000);
            renderer->draw_text(m_name, tx, ty, 0xFFFFFFFF);
        }
    }

    void perform_layout(gui::BoxConstraints constraints) override {
        m_rect.w = 80;
        m_rect.h = 100;
        gui::Size size = constraints.constrain({m_rect.w, m_rect.h});
        m_rect.w = size.w;
        m_rect.h = size.h;
    }

    void set_name(const char* name) { m_name = name; }
    void set_icon(gui::widgets::IconType icon) { m_icon = icon; }
    void set_hovered(bool h) { m_hovered = h; }
    void set_pressed(bool p) { m_pressed = p; }

private:
    const char* m_name;
    gui::widgets::IconType m_icon;
    bool m_hovered;
    bool m_pressed;
};

ShortcutWidget::ShortcutWidget(const char* name, gui::widgets::IconType icon, const char* exec_path)
    : m_name(name), m_icon_type(icon), m_exec_path(exec_path), m_click_timer(0) {
    m_rect = {0, 0, 80, 100};
}

gui::Ref<gui::RenderObject> ShortcutWidget::create_render_object() {
    return gui::UIContext::get().region().alloc<RenderShortcut>();
}

void ShortcutWidget::update_render_object(gui::Ref<gui::RenderObject> render_object) {
    gui::Widget::update_render_object(render_object);
    auto rs = static_cast<RenderShortcut*>(render_object.operator->());
    rs->set_name(m_name);
    rs->set_icon(m_icon_type);
    rs->set_hovered(m_state == gui::WidgetState::Hovered);
    rs->set_pressed(m_state == gui::WidgetState::Pressed);
}

void ShortcutWidget::on_event(gui::Event& event) {
    const auto& raw = event.raw;

    if (raw.type == acos::input::InputType::Mouse) {
        if (event.phase == gui::EventPhase::Target) {
            if (raw.value == 1) { // Left Button Pressed
                m_state = gui::WidgetState::Pressed;
                set_paint_dirty();

                if (m_click_timer > 0) {
                    // Double Clicked!
                    if (m_exec_path) {
                        // Open application via shell hooks
                        if (strcmp(m_exec_path, "terminal") == 0) DesktopShell::get().launch_terminal();
                        else if (strcmp(m_exec_path, "files") == 0) DesktopShell::get().launch_file_manager();
                        else if (strcmp(m_exec_path, "settings") == 0) DesktopShell::get().launch_settings();
                    }
                    m_click_timer = 0;
                } else {
                    m_click_timer = 500; // 500ms window for second click
                }
            } else if (raw.value == 0) { // Released
                m_state = gui::WidgetState::Hovered;
                set_paint_dirty();
            }
        }
    }
}

void ShortcutWidget::update(u64 delta_ms) {
    gui::Widget::update(delta_ms);
    if (m_click_timer > 0) {
        if (delta_ms >= m_click_timer) m_click_timer = 0;
        else m_click_timer -= delta_ms;
    }
}

} // namespace acos::shell
