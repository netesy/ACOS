#include <acos/process.h>
#include <acos/runtime.h>
#include "event_dispatcher.h"
#include "context.h"
#include "../widget.h"

namespace acos::gui {

void EventDispatcher::dispatch(const ::acos::abi::InputEvent& raw, Ref<Widget> root) {
    if (!root) return;

    Event event(raw);

    if (raw.type == ::acos::abi::InputType::Mouse) {
        event.mouse_x = (::acos::i32)((raw.code >> 16) & 0xFFFF);
        event.mouse_y = (::acos::i32)(raw.code & 0xFFFF);

        Ref<Widget> target = perform_hit_test(root, event.mouse_x, event.mouse_y);
        if (target) {
            event.target = target;
            route_event(event, target);
        }
    } else {
        Ref<Widget> focused = UIContext::get().focus_manager().focused();
        if (focused) {
            event.target = focused;
            route_event(event, focused);
        } else {
            route_event(event, root);
        }
    }
}

Ref<Widget> EventDispatcher::perform_hit_test(Ref<Widget> root, ::acos::i32 x, ::acos::i32 y) {
    if (!root || !root->is_visible() || !root->hit_test(x, y)) return Ref<Widget>();

    const auto& children = root->children();
    for (int i = (int)children.size() - 1; i >= 0; i--) {
        Ref<Widget> target = perform_hit_test(children[i], x, y);
        if (target) return target;
    }

    return root;
}

void EventDispatcher::route_event(Event& event, Ref<Widget> target) {
    if (!target) return;

    event.phase = EventPhase::Target;
    target->handle_event(event);

    if (event.handled) return;

    event.phase = EventPhase::Bubble;
    Ref<Widget> parent = target->parent();
    while (parent && !event.handled) {
        parent->handle_event(event);
        parent = parent->parent();
    }
}

} // namespace acos::gui
