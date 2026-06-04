#pragma once
#include <kernel/input/input_device.h>
#include "ref.h"

namespace acos::gui {

class Widget;

enum class EventPhase {
    Capture,
    Target,
    Bubble
};

struct Event {
    const acos::input::InputEvent& raw;
    EventPhase phase;
    Ref<Widget> target;
    bool handled;

    i32 mouse_x, mouse_y;

    Event(const acos::input::InputEvent& r)
        : raw(r), phase(EventPhase::Target), handled(false), mouse_x(0), mouse_y(0) {}

    void stop_propagation() { handled = true; }
};

class EventDispatcher {
public:
    void dispatch(const acos::input::InputEvent& raw, Ref<Widget> root);

private:
    Ref<Widget> perform_hit_test(Ref<Widget> root, i32 x, i32 y);
    void route_event(Event& event, Ref<Widget> target);
};

} // namespace acos::gui
