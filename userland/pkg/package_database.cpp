#include <acos/process.h>
#include <acos/runtime.h>
#include "package_database.h"

namespace acos::pkg {

// Helper function for string comparison
static inline int strcmp_impl(const char* a, const char* b) {
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

PackageDatabase::PackageDatabase() : m_count(0) {}

bool PackageDatabase::initialize() {
    m_count = 0;
    for (usize i = 0; i < MAX_INSTALLED; i++) {
        m_installed[i].manifest.name[0] = '\0';
    }
    return true;
}

bool PackageDatabase::register_package(const Package& pkg) {
    if (m_count >= MAX_INSTALLED) return false;
    
    m_installed[m_count].manifest = pkg.manifest();
    m_installed[m_count].install_date[0] = '\0';
    m_installed[m_count].install_size = 0;
    m_count++;
    
    return true;
}

bool PackageDatabase::unregister_package(const char* name) {
    if (!name) return false;
    
    for (usize i = 0; i < m_count; i++) {
        if (strcmp_impl(m_installed[i].manifest.name, name) == 0) {
            m_installed[i] = m_installed[--m_count];
            return true;
        }
    }
    return false;
}

bool PackageDatabase::is_installed(const char* name) {
    if (!name) return false;
    
    for (usize i = 0; i < m_count; i++) {
        if (strcmp_impl(m_installed[i].manifest.name, name) == 0) {
            return true;
        }
    }
    return false;
}

const InstalledPackage* PackageDatabase::get_package(const char* name) {
    if (!name) return nullptr;
    
    for (usize i = 0; i < m_count; i++) {
        if (strcmp_impl(m_installed[i].manifest.name, name) == 0) {
            return &m_installed[i];
        }
    }
    return nullptr;
}

} // namespace acos::pkg
