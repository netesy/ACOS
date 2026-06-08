#include "telemetry_widgets.h"
#include <userland/gui/core/render_widgets.h>
#include <userland/gui/core/context.h>
#include <userland/gui/theme.h>

namespace acos::shell {

// Storage Card Render Object
class RenderStorageCard : public gui::widgets::RenderPanel {
public:
    void paint(::acos::graphics::Renderer* renderer) override {
        gui::widgets::RenderPanel::paint(renderer);
        if (!renderer) return;

        renderer->draw_text("SSD MOUNTED", m_rect.x + 15, m_rect.y + 45, 0xFFFFFFFF);
        renderer->draw_text("82%", m_rect.x + m_rect.w - 45, m_rect.y + 45, 0xFFFFFFFF);
        
        // Custom progress bar rendering
        u32 bar_w = m_rect.w - 30;
        u32 bar_h = 8;
        renderer->fill_rounded_rect(m_rect.x + 15, m_rect.y + 70, bar_w, bar_h, 4, 0x44FFFFFF);
        renderer->fill_rounded_rect(m_rect.x + 15, m_rect.y + 70, (bar_w * 82) / 100, bar_h, 4, 0xFFBF00FF);
    }
};

// Recent Logs Render Object
class RenderRecentLogs : public gui::widgets::RenderPanel {
public:
    void paint(::acos::graphics::Renderer* renderer) override {
        gui::widgets::RenderPanel::paint(renderer);
        if (!renderer) return;

        struct Log { const char* title; const char* sub; u32 color; };
        Log logs[] = {
            {"process_exec(0.01)", "PID: 4122 | State: SLEEPING", 0xFF00E5FF},
            {"network_stack_init", "Packet drop: 0% | Latency: 2ms", 0xFFBF00FF},
            {"unauthorized_access_trap", "Blocked IP: 192.168.1.104", 0xFFFF1744}
        };

        u32 cur_y = m_rect.y + 50;
        for (int i = 0; i < 3; i++) {
            renderer->fill_circle(m_rect.x + 25, cur_y + 12, 4, logs[i].color);
            renderer->draw_text(logs[i].title, m_rect.x + 45, cur_y, 0xFFFFFFFF);
            renderer->draw_text(logs[i].sub, m_rect.x + 45, cur_y + 18, 0xFF888888);
            cur_y += 45;
        }
    }
};

// CPULoadWidget implementation
CPULoadWidget::CPULoadWidget() : m_head(0), m_accumulated_ms(0) {
    for (int i = 0; i < 64; i++) m_history[i] = 0.0f;
}

gui::Ref<gui::RenderObject> CPULoadWidget::create_render_object() {
    return gui::UIContext::get().region().alloc<gui::widgets::RenderGraph>();
}

void CPULoadWidget::update_render_object(gui::Ref<gui::RenderObject> render_object) {
    gui::widgets::Panel::update_render_object(render_object);
    auto rg = static_cast<gui::widgets::RenderGraph*>(render_object.operator->());
    rg->set_data(m_history, 64);
}

void CPULoadWidget::update(u64 delta_ms) {
    gui::Widget::update(delta_ms);
    m_accumulated_ms += delta_ms;
    
    if (m_accumulated_ms >= 500) { // Update every 500ms
        m_accumulated_ms = 0;
        
        // Simulate CPU load for now, or pull from kernel if available
        static u64 seed = 12345;
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        float load = (float)(seed % 100) / 100.0f;
        
        m_history[m_head] = load;
        m_head = (m_head + 1) % 64;
        set_paint_dirty();
    }
}

// StorageCardWidget implementation
StorageCardWidget::StorageCardWidget() : m_usage_percent(0) {}

gui::Ref<gui::RenderObject> StorageCardWidget::create_render_object() {
    return gui::UIContext::get().region().alloc<RenderStorageCard>();
}

void StorageCardWidget::update_render_object(gui::Ref<gui::RenderObject> render_object) {
    gui::widgets::Panel::update_render_object(render_object);
    // Could update a progress bar child here if we added one
}

void StorageCardWidget::update(u64 delta_ms) {
    gui::Widget::update(delta_ms);
    // Query VFS for disk usage
    // For now we'll keep the static 82% from the design spec
    m_usage_percent = 82;
}

// RecentLogsWidget implementation
RecentLogsWidget::RecentLogsWidget() {}

gui::Ref<gui::RenderObject> RecentLogsWidget::create_render_object() {
    return gui::UIContext::get().region().alloc<RenderRecentLogs>();
}

void RecentLogsWidget::update_render_object(gui::Ref<gui::RenderObject> render_object) {
    gui::widgets::Panel::update_render_object(render_object);
}

} // namespace acos::shell
