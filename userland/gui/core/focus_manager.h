#pragma once
#include "ref.h"

namespace acos::gui {

class Widget;

class FocusManager {
public:
    FocusManager() : m_focused() {}

    void set_focus(Ref<Widget> widget);
    Ref<Widget> focused() const { return m_focused; }

private:
    Ref<Widget> m_focused;
};

} // namespace acos::gui
