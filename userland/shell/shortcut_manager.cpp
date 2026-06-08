#include "shortcut_manager.h"
#include <kernel/vfs/vfs.h>
#include <userland/gui/core/context.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::shell {

DesktopShortcutManager::DesktopShortcutManager() {}

void DesktopShortcutManager::update() {}

void DesktopShortcutManager::sync() {
    const char* desktop_path = "/userland/desktop/";
    acos::vfs::DirectoryEntry entries[32];
    i32 count = acos::vfs::VFS::read_dir(desktop_path, entries, 32);

    if (count < 0) return;

    m_shortcuts.clear();
    if (m_grid) {
        // Clear existing children
        const auto& children = m_grid->children();
        acos::Vector<gui::Ref<gui::Widget>> to_remove;
        for (auto& child : children) {
            if (child) to_remove.push_back(child);
        }
        for (auto& child : to_remove) {
            m_grid->remove_child(child);
        }
    }

    for (i32 i = 0; i < count; i++) {
        // Skip non-desk files
        usize len = strlen(entries[i].name);
        if (len < 6 || strcmp(entries[i].name + len - 5, ".desk") != 0) continue;

        // Found a shortcut file
        sync_file(desktop_path, entries[i].name);
    }

    if (m_grid) {
        for (auto& s : m_shortcuts) {
            m_grid->add_child(s.static_cast_to<gui::Widget>());
        }
        m_grid->set_layout_dirty();
    }
}

void DesktopShortcutManager::sync_file(const char* dir, const char* name) {
    char full_path[512];
    usize dlen = strlen(dir);
    memcpy(full_path, dir, dlen);
    memcpy(full_path + dlen, name, strlen(name) + 1);

    i32 fd = acos::vfs::VFS::open(full_path, 0);
    if (fd < 0) return;

    char buffer[1024];
    i32 bytes = acos::vfs::VFS::read(fd, buffer, 1023);
    acos::vfs::VFS::close(fd);
    if (bytes <= 0) return;
    buffer[bytes] = '\0';

    char app_name[64] = "Unknown";
    char exec_path[256] = "";
    gui::widgets::IconType icon_type = gui::widgets::IconType::Files;

    // Simple line-based parser
    char* line = buffer;
    while (*line) {
        char* next_line = line;
        while (*next_line && *next_line != '\n') next_line++;
        if (*next_line == '\n') {
            *next_line = '\0';
            next_line++;
        }

        if (strncmp(line, "Name=", 5) == 0) {
            memcpy(app_name, line + 5, strlen(line + 5) + 1);
        } else if (strncmp(line, "Exec=", 5) == 0) {
            memcpy(exec_path, line + 5, strlen(line + 5) + 1);
        } else if (strncmp(line, "Icon=", 5) == 0) {
            if (strcmp(line + 5, "Terminal") == 0) icon_type = gui::widgets::IconType::Terminal;
        }

        line = next_line;
    }

    auto& region = gui::UIContext::get().region();
    auto shortcut = region.alloc<ShortcutWidget>(app_name, icon_type, exec_path);
    m_shortcuts.push_back(shortcut);
}

} // namespace acos::shell
