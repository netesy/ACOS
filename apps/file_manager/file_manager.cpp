#include "file_manager.h"
#include <userland/gui/core/context.h>
#include <libs/runtime/include/acos/runtime.h>
#include <kernel/vfs/vfs.h>

namespace acos::apps {

FileManager::FileManager() : gui::WindowWidget("File Manager", 200, 150, 400, 350) {
    auto& region = gui::UIContext::get().region();

    m_file_list = region.alloc<gui::widgets::ListView>();
    if (m_file_list) {
        m_file_list->set_rect({10, 40, 380, 240});
        add_child(m_file_list.static_cast_to<gui::Widget>());
    }

    auto btn_row = region.alloc<gui::widgets::Row>();
    btn_row->set_rect({10, 290, 380, 32});

    auto open_btn = region.alloc<gui::widgets::Button>("Open");
    auto back_btn = region.alloc<gui::widgets::Button>("Back");

    btn_row->add_child(back_btn.static_cast_to<gui::Widget>());
    btn_row->add_child(open_btn.static_cast_to<gui::Widget>());
    
    add_child(btn_row.static_cast_to<gui::Widget>());

    m_current_path[0] = '/';
    m_current_path[1] = '\0';
    browse(m_current_path);
}

void FileManager::browse(const char* path) {
    if (!path || !m_file_list) return;

    m_file_list->clear();

    acos::vfs::DirectoryEntry entries[32];
    i32 count = acos::vfs::VFS::read_dir(path, entries, 32);

    if (count < 0) {
        m_file_list->add_item("Error reading directory");
        return;
    }

    for (i32 i = 0; i < count; i++) {
        char full_name[260];
        usize j = 0;
        while (entries[i].name[j]) {
            full_name[j] = entries[i].name[j];
            j++;
        }
        if (entries[i].type == acos::vfs::NodeType::Directory) {
            full_name[j++] = '/';
        }
        full_name[j] = '\0';
        m_file_list->add_item(full_name);
    }
}

} // namespace acos::apps
