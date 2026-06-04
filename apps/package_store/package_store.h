#pragma once
#include <window_widget.h>
#include <listview.h>
#include <button.h>

namespace acos::apps {

class PackageStore : public ui::WindowWidget {
public:
    PackageStore();

private:
    ui::ListView m_pkg_list;
    ui::Button m_install_btn;
};

} // namespace acos::apps
