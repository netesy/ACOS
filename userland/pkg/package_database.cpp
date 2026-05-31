#include "package_database.h"
#include <libs/runtime/include/acos/runtime.h>

namespace acos::pkg {

PackageDatabase::PackageDatabase() : m_count(0) {}

bool PackageDatabase::initialize() {
    return true;
}

bool PackageDatabase::register_package(const Package& pkg) {
    if (m_count >= MAX_INSTALLED) return false;
    m_installed[m_count].manifest = pkg.manifest();
    m_count++;
    return true;
}

bool PackageDatabase::unregister_package(const char* name) {
    (void)name;
    return true;
}

bool PackageDatabase::is_installed(const char* name) {
    (void)name;
    return false;
}

const InstalledPackage* PackageDatabase::get_package(const char* name) {
    (void)name;
    return nullptr;
}

} // namespace acos::pkg
