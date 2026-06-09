#pragma once
#include <userland/gui/widget.h>
#include <userland/gui/icon.h>

namespace acos::shell {

class ShortcutWidget : public gui::Widget {
public:
    ShortcutWidget(const char* name, gui::widgets::IconType icon, const char* exec_path);

    gui::Ref<gui::RenderObject> create_render_object() override;
    void update_render_object(gui::Ref<gui::RenderObject> render_object) override;

    void on_event(gui::Event& event) override;
    void update(u64 delta_ms) override;

    const char* name() const { return m_name; }
    const char* exec_path() const { return m_exec_path; }

private:
    const char* m_name;
    gui::widgets::IconType m_icon_type;
    const char* m_exec_path;
    u64 m_click_timer;
};

} // namespace acos::shell
