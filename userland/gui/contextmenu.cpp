#include "contextmenu.h"

namespace acos::gui::widgets {

ContextMenu::ContextMenu() {
    set_visible(false);
}

void ContextMenu::popup(i32 x, i32 y) {
    set_position(x, y);
    set_visible(true);
}

} // namespace acos::gui::widgets
