#pragma once
#include "dialog.h"
#include "listview.h"

namespace acos::gui::widgets {

class FileDialog : public Dialog {
public:
    FileDialog();
    ~FileDialog() override;

    void open_directory(const char* path);
    const char* selected_file() const;

private:
    Ref<ListView> m_list_view;
    char m_selected[256];
};

} // namespace acos::gui::widgets
