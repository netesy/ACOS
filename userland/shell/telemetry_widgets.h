#pragma once
#include <userland/gui/widget.h>
#include <userland/gui/panel.h>

namespace acos::shell {

class CPULoadWidget : public gui::widgets::Panel {
public:
    CPULoadWidget();
    gui::Ref<gui::RenderObject> create_render_object() override;
    void update_render_object(gui::Ref<gui::RenderObject> render_object) override;
    void update(u64 delta_ms) override;
private:
    float m_history[64];
    u32 m_head;
    u64 m_accumulated_ms;
};

class StorageCardWidget : public gui::widgets::Panel {
public:
    StorageCardWidget();
    gui::Ref<gui::RenderObject> create_render_object() override;
    void update_render_object(gui::Ref<gui::RenderObject> render_object) override;
    void update(u64 delta_ms) override;
private:
    [[maybe_unused]] u32 m_usage_percent;
};

class RecentLogsWidget : public gui::widgets::Panel {
public:
    RecentLogsWidget();
    gui::Ref<gui::RenderObject> create_render_object() override;
    void update_render_object(gui::Ref<gui::RenderObject> render_object) override;
private:
    // Log entries storage
};

} // namespace acos::shell
