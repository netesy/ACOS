#pragma once
#include <window_widget.h>
#include <listview.h>

namespace acos::apps {

class FileManager : public ui::WindowWidget {
public:
    FileManager();
    void browse(const char* path);
    void navigate_to(const char* entry_name);
    void navigate_parent();

private:
    ui::ListView m_file_list;
    char m_current_path[256];
    
    // Helper methods
    void enumerate_directory(const char* path);
    void enumerate_directory_fallback(const char* path);
    bool is_directory(const char* entry_name);
};

} // namespace acos::apps
