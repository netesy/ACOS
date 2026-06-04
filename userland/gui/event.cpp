#include "event.h"
#include "render_object.h"
#include "context.h"
#include "focus_manager.h"

namespace acos::ui {

Ref<RenderObject> EventDispatcher::hit_test_recursive(UIContext* ctx, Ref<RenderObject> node, Position point, Position offset) {
    if (node.is_null()) return Ref<RenderObject>::null();
    RenderObject* obj = node.get(ctx);
    if (!obj->hit_test(ctx, point, offset)) return Ref<RenderObject>::null();
    Position local_offset = { offset.x + obj->position().x, offset.y + obj->position().y };
    Ref<RenderObject> target = Ref<RenderObject>::null();
    Ref<RenderObject> child = obj->first_child();
    while (!child.is_null()) {
        Ref<RenderObject> hit = hit_test_recursive(ctx, child, point, local_offset);
        if (!hit.is_null()) target = hit;
        child = child.get(ctx)->next_sibling();
    }
    return target.is_null() ? node : target;
}

void EventDispatcher::dispatch(UIContext* ctx, Ref<RenderObject> root, UIEvent& event) {
    if (root.is_null()) return;
    if (event.type == EventType::MouseDown || event.type == EventType::MouseMove || event.type == EventType::MouseUp) {
        Ref<RenderObject> target = hit_test_recursive(ctx, root, {event.mouse.x, event.mouse.y}, {0, 0});
        if (!target.is_null()) propagate_event(ctx, target, event);
    } else if (event.type == EventType::KeyDown || event.type == EventType::KeyUp) {
        Ref<RenderObject> target = ctx->focus_manager().focused_node();
        if (!target.is_null()) propagate_event(ctx, target, event);
    }
}

void EventDispatcher::propagate_event(UIContext* ctx, Ref<RenderObject> target, UIEvent& event) {
    Ref<RenderObject> path[64]; u32 depth = 0;
    Ref<RenderObject> current = target;
    while (!current.is_null() && depth < 64) { path[depth++] = current; current = current.get(ctx)->parent(); }
    for (i32 i = depth - 1; i >= 0; --i) {
        path[i].get(ctx)->handle_event(ctx, event, EventPhase::Capture);
        if (event.handled) return;
    }
    for (u32 i = 0; i < depth; ++i) {
        path[i].get(ctx)->handle_event(ctx, event, EventPhase::Bubble);
        if (event.handled) return;
    }
}

} // namespace acos::ui
