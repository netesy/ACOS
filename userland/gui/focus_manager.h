#pragma once
#include "ref.h"
#include "event.h"

namespace acos::ui {

class RenderObject;
class UIContext;

class FocusManager {
public:
    FocusManager();
    Ref<RenderObject> focused_node() const { return m_focused_node; }
    void request_focus(UIContext* ctx, Ref<RenderObject> node);
    void clear_focus(UIContext* ctx);
private:
    Ref<RenderObject> m_focused_node;
};

} // namespace acos::ui
