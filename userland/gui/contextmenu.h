#pragma once
#include "menu.h"

namespace acos::gui::widgets {

class ContextMenu : public Menu {
public:
    ContextMenu();
    void popup(i32 x, i32 y);
};

} // namespace acos::gui::widgets
