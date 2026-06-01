#include "package_database.h"
#include <libs/runtime/include/acos/runtime.h>

namespace acos::pkg {

PackageDatabase::PackageDatabase() : m_count(0) {}

bool PackageDatabase::initialize() {
    m_count = 0;
    for (usize i = 0; i < MAX_INSTALLED; i++) {
        m_installed[i].manifest.name = nullptr;
    }
    return true;
}

bool PackageDatabase::register_package(const Package& pkg) {
    if (m_count >= MAX_INSTALLED) return false;
    
    m_installed[m_count].manifest = pkg.manifest();
    m_installed[m_count].install_time = 0;
    m_installed[m_count].size = 0;
    m_count++;
    
    return true;
}

bool PackageDatabase::unregister_package(const char* name) {
    if (!name) return false;
    
    for (usize i = 0; i < m_count; i++) {
        if (acos::runtime::strcmp(m_installed[i].manifest.name, name) == 0) {
            m_installed[i] = m_installed[--m_count];
            return true;
        }
    }
    return false;
}

bool PackageDatabase::is_installed(const char* name) {
    if (!name) return false;
    
    for (usize i = 0; i < m_count; i++) {
        if (acos::runtime::strcmp(m_installed[i].manifest.name, name) == 0) {
            return true;
        }
    }
    return false;
}

const InstalledPackage* PackageDatabase::get_package(const char* name) {
    if (!name) return nullptr;
    
    for (usize i = 0; i < m_count; i++) {
        if (acos::runtime::strcmp(m_installed[i].manifest.name, name) == 0) {
            return &m_installed[i];
        }
    }
    return nullptr;
}

} // namespace acos::pkg
