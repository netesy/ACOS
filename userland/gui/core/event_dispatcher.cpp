#include "event_dispatcher.h"
#include "context.h"
#include "../widget.h"

namespace acos::gui {

void EventDispatcher::dispatch(const acos::input::InputEvent& raw, Ref<Widget> root) {
    if (!root) return;

    Ref<Widget> target;

    if (raw.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((raw.code >> 16) & 0xFFFF);
        i32 my = (i32)(raw.code & 0xFFFF);
        target = perform_hit_test(root, mx, my);
    } else if (raw.type == acos::input::InputType::Keyboard) {
        target = UIContext::get().focus_manager().focused();
        if (!target) target = root;
    }

    if (target) {
        Event event(raw);
        event.target = target;
        if (raw.type == acos::input::InputType::Mouse) {
            event.mouse_x = (i32)((raw.code >> 16) & 0xFFFF);
            event.mouse_y = (i32)(raw.code & 0xFFFF);
        }
        route_event(event, target);
    }
}

Ref<Widget> EventDispatcher::perform_hit_test(Ref<Widget> root, i32 x, i32 y) {
    if (!root->hit_test(x, y)) return Ref<Widget>();

    const auto& children = root->children();
    // Hit test from top to bottom (reverse order of children for correct Z-order)
    for (i32 i = children.size() - 1; i >= 0; i--) {
        Ref<Widget> child = children[i];
        if (child && child->is_visible()) {
            Ref<Widget> hit = perform_hit_test(child, x, y);
            if (hit) return hit;
        }
    }

    return root;
}

void EventDispatcher::route_event(Event& event, Ref<Widget> target) {
    // Collect path from root to target
    Vector<Ref<Widget>> path;
    Ref<Widget> current = target;
    while (current) {
        path.push_back(current);
        current = current->parent();
    }

    // Phase 1: Capture (Root to Target Parent)
    event.phase = EventPhase::Capture;
    for (i32 i = path.size() - 1; i > 0; i--) {
        path[i]->handle_event(event);
        if (event.handled) return;
    }

    // Phase 2: Target
    event.phase = EventPhase::Target;
    path[0]->handle_event(event);
    if (event.handled) return;

    // Phase 3: Bubble (Target Parent to Root)
    event.phase = EventPhase::Bubble;
    for (u32 i = 1; i < path.size(); i++) {
        path[i]->handle_event(event);
        if (event.handled) return;
    }
}

} // namespace acos::gui
