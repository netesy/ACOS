#pragma once
#include "menu.h"

namespace acos::gui {

class ContextMenu : public Menu {
public:
    ContextMenu();
    void popup(i32 x, i32 y);
};

} // namespace acos::gui
