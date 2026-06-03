#pragma once
#include <ui/window_widget.h>
#include <ui/listview.h>
#include <ui/button.h>

namespace acos::apps {

class PackageStore : public ui::WindowWidget {
public:
    PackageStore();

private:
    ui::ListView m_pkg_list;
    ui::Button m_install_btn;
};

} // namespace acos::apps
