#pragma once
#include <userland/gui/window_widget.h>
#include <userland/gui/listview.h>
#include <userland/gui/button.h>

namespace acos::apps {

class PackageStore : public gui::WindowWidget {
public:
    PackageStore();

private:
    gui::ListView m_pkg_list;
    gui::Button m_install_btn;
};

} // namespace acos::apps
