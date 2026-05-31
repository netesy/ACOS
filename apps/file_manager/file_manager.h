#pragma once
#include <userland/gui/window_widget.h>
#include <userland/gui/listview.h>

namespace acos::apps {

class FileManager : public gui::WindowWidget {
public:
    FileManager();
    void browse(const char* path);

private:
    gui::ListView m_file_list;
};

} // namespace acos::apps
