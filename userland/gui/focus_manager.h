#pragma once
#include "ref.h"

namespace acos::ui {

class RenderObject;

class FocusManager {
public:
    FocusManager();
    Ref<RenderObject> focused_node() const { return m_focused_node; }
    void set_focus(Ref<RenderObject> node);
private:
    Ref<RenderObject> m_focused_node;
};

} // namespace acos::ui
