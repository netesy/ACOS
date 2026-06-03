#pragma once
#include <ui/ref.h>
#include <acos/types.h>

namespace acos::ui {

class Widget;
class UIContext;

enum class EventType {
    MouseDown,
    MouseUp,
    MouseMove,
    KeyDown,
    KeyUp,
    FocusIn,
    FocusOut
};

struct UIEvent {
    EventType type;
    bool handled = false;

    union {
        struct {
            i32 x, y;
            u32 button;
        } mouse;
        struct {
            u32 key;
            u32 modifiers;
        } key;
    };

    void consume() { handled = true; }
};

class EventDispatcher {
public:
    void dispatch(UIContext* ctx, Ref<Widget> root, UIEvent& event);
private:
    void capture_phase(UIContext* ctx, Ref<Widget> target, UIEvent& event);
    void bubble_phase(UIContext* ctx, Ref<Widget> target, UIEvent& event);
};

} // namespace acos::ui
