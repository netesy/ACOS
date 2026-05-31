#include "package_store.h"

namespace acos::apps {

PackageStore::PackageStore() : gui::WindowWidget("Package Store", 50, 50, 600, 450),
                               m_install_btn("Install") {
    add_child(&m_pkg_list);
    add_child(&m_install_btn);

    m_pkg_list.set_position(60, 100);
    m_pkg_list.set_size(580, 300);
    m_install_btn.set_position(500, 410);
}

} // namespace acos::apps
