#pragma once
#include <userland/gui/widget.h>
#include <userland/gui/core/vector.h>
#include <userland/gui/core/grid.h>
#include "shortcut_widget.h"

namespace acos::shell {

struct ShortcutInfo {
    char name[64];
    char exec_path[256];
    gui::widgets::IconType icon;
};

class DesktopShortcutManager {
public:
    DesktopShortcutManager();
    void update();
    void sync();
    void set_grid(gui::Ref<gui::widgets::Grid> grid) { m_grid = grid; }

    const acos::Vector<gui::Ref<ShortcutWidget>>& shortcuts() const { return m_shortcuts; }

private:
    void sync_file(const char* dir, const char* name);
    acos::Vector<gui::Ref<ShortcutWidget>> m_shortcuts;
    gui::Ref<gui::widgets::Grid> m_grid;
};

} // namespace acos::shell
