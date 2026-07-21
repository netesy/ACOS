#include <acos/process.h>
#include <acos/runtime.h>
#include "file_manager.h"
#include <acos/vfs.h>
#include <userland/gui/core/context.h>
#include <userland/gui/button.h>
#include <userland/gui/listview.h>
#include <userland/gui/core/flex.h>
#include <libs/runtime/include/acos/runtime.h>

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
    open_btn->on_click(on_open_clicked, this);

    auto back_btn = region.alloc<gui::widgets::Button>("Back");
    back_btn->on_click(on_back_clicked, this);

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

    acos::abi::DirectoryEntry entries[32];
    i32 count = acos::vfs::read_dir(path, entries, 32);

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

void FileManager::open_selected() {
    if (!m_file_list) return;
    i32 sel = m_file_list->get_selected();
    if (sel < 0) return;

    const char* name = m_file_list->get_item(sel);
    if (!name) return;

    // Construct full path
    char next_path[512];
    usize len = 0;
    while (m_current_path[len]) {
        next_path[len] = m_current_path[len];
        len++;
    }
    if (len > 0 && next_path[len - 1] != '/') {
        next_path[len++] = '/';
    }

    usize name_len = 0;
    while (name[name_len]) {
        next_path[len + name_len] = name[name_len];
        name_len++;
    }
    next_path[len + name_len] = '\0';

    // If it's a directory (ends with '/'), browse into it
    if (name_len > 0 && name[name_len - 1] == '/') {
        // Strip trailing '/'
        next_path[len + name_len - 1] = '\0';

        // Copy to current path
        usize i = 0;
        while (next_path[i]) {
            m_current_path[i] = next_path[i];
            i++;
        }
        m_current_path[i] = '\0';
        browse(m_current_path);
    }
}

void FileManager::go_back() {
    if (::strcmp(m_current_path, "/") == 0) return;

    usize len = ::strlen(m_current_path);
    if (len == 0) return;

    if (len > 1 && m_current_path[len - 1] == '/') {
        m_current_path[len - 1] = '\0';
        len--;
    }

    while (len > 0 && m_current_path[len - 1] != '/') {
        len--;
    }

    if (len > 0) {
        m_current_path[len] = '\0';
    } else {
        m_current_path[0] = '/';
        m_current_path[1] = '\0';
    }
    browse(m_current_path);
}

void FileManager::on_open_clicked(void* arg) {
    auto* fm = static_cast<FileManager*>(arg);
    if (fm) fm->open_selected();
}

void FileManager::on_back_clicked(void* arg) {
    auto* fm = static_cast<FileManager*>(arg);
    if (fm) fm->go_back();
}

} // namespace acos::apps
