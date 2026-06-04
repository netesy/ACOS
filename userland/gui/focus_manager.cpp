#include "focus_manager.h"
#include "render_object.h"
#include "context.h"

namespace acos::ui {

FocusManager::FocusManager() : m_focused_node(Ref<RenderObject>::null()) {}

void FocusManager::request_focus(UIContext* ctx, Ref<RenderObject> node) {
    if (m_focused_node.index == node.index && m_focused_node.generation == node.generation) return;
    if (!m_focused_node.is_null()) {
        UIEvent ev; ev.type = EventType::FocusOut;
        m_focused_node.get(ctx)->handle_event(ctx, ev, EventPhase::Bubble);
    }
    m_focused_node = node;
    if (!m_focused_node.is_null()) {
        UIEvent ev; ev.type = EventType::FocusIn;
        m_focused_node.get(ctx)->handle_event(ctx, ev, EventPhase::Bubble);
    }
}

void FocusManager::clear_focus(UIContext* ctx) { request_focus(ctx, Ref<RenderObject>::null()); }

} // namespace acos::ui
