#include "file_manager.h"

namespace acos::apps {

FileManager::FileManager() : gui::WindowWidget("File Manager", 100, 100, 500, 400) {
    add_child(&m_file_list);
    m_file_list.set_position(110, 140);
    m_file_list.set_size(480, 350);
}

void FileManager::browse(const char* path) {
    (void)path;
    // Enumerate files via VFS
}

} // namespace acos::apps
