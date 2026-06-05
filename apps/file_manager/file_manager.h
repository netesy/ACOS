#pragma once
#include <userland/gui/window_widget.h>
#include <userland/gui/listview.h>

namespace acos::apps {

class FileManager : public gui::WindowWidget {
public:
    FileManager();
    void browse(const char* path);

private:
    gui::Ref<gui::widgets::ListView> m_file_list;
    char m_current_path[256];
};

} // namespace acos::apps
