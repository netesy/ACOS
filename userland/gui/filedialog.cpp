#include "filedialog.h"
#include "core/context.h"
#include <acos/vfs.h>

namespace acos::gui::widgets {

FileDialog::FileDialog() : Dialog("Open File", 400, 300) {
    m_rect = {50, 50, 400, 300};
    m_selected[0] = '\0';

    auto& region = UIContext::get().region();
    m_list_view = region.alloc<ListView>();
    m_list_view->set_rect({10, 40, 380, 240});
    add_child(m_list_view.static_cast_to<Widget>());

    open_directory("/");
}

FileDialog::~FileDialog() {}

void FileDialog::open_directory(const char* path) {
    if (!path) return;
    m_list_view->clear();

    static vfs::DirectoryEntry entries[32];
    i32 n = vfs::read_dir(path, entries, 32);
    if (n >= 0) {
        for (i32 i = 0; i < n; i++) {
            m_list_view->add_item(entries[i].name);
        }
    }
}

const char* FileDialog::selected_file() const {
    i32 sel = m_list_view->get_selected();
    if (sel >= 0) {
        // Return selected item name
    }
    return nullptr;
}

} // namespace acos::gui::widgets
