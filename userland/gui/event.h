#pragma once
#include "ref.h"
#include "geometry.h"

namespace acos::ui {

class RenderObject;
class UIContext;

enum class EventType { MouseDown, MouseUp, MouseMove, KeyDown, KeyUp, FocusIn, FocusOut };
enum class EventPhase { Capture, Bubble };

struct UIEvent {
    EventType type;
    bool handled = false;
    union {
        struct { i32 x, y; u32 button; } mouse;
        struct { u32 key; u32 modifiers; } key;
    };
    void consume() { handled = true; }
};

class EventDispatcher {
public:
    void dispatch(UIContext* ctx, Ref<RenderObject> root, UIEvent& event);
private:
    Ref<RenderObject> hit_test_recursive(UIContext* ctx, Ref<RenderObject> node, Position point, Position offset);
    void propagate_event(UIContext* ctx, Ref<RenderObject> target, UIEvent& event);
};

} // namespace acos::ui
