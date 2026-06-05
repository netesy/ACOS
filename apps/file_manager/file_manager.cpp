#include "file_manager.h"
#include <userland/gui/core/context.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::apps {

FileManager::FileManager() : gui::WindowWidget("File Manager", 200, 150, 400, 350) {
    auto& region = gui::UIContext::get().region();
    
    m_file_list = region.alloc<gui::widgets::ListView>();
    if (m_file_list) {
        m_file_list->set_rect({10, 40, 380, 240});
        
        // Mock root directory
        m_file_list->add_item("..");
        m_file_list->add_item("bin/");
        m_file_list->add_item("etc/");
        m_file_list->add_item("home/");
        m_file_list->add_item("lib/");
        m_file_list->add_item("root/");
        m_file_list->add_item("tmp/");
        m_file_list->add_item("usr/");
        m_file_list->add_item("var/");
        m_file_list->add_item("README.md");
        m_file_list->add_item("kernel.elf");
        
        add_child(m_file_list.static_cast_to<gui::Widget>());
    }

    auto btn_row = region.alloc<gui::widgets::Row>();
    btn_row->set_rect({10, 290, 380, 32});
    
    auto open_btn = region.alloc<gui::widgets::Button>("Open");
    auto back_btn = region.alloc<gui::widgets::Button>("Back");
    
    btn_row->add_child(back_btn.static_cast_to<gui::Widget>());
    btn_row->add_child(open_btn.static_cast_to<gui::Widget>());
    
    add_child(btn_row.static_cast_to<gui::Widget>());
}

void FileManager::browse(const char* path) {
    (void)path;
}

} // namespace acos::apps
