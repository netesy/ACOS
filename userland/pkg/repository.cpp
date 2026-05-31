#include "repository.h"

namespace acos::pkg {

Repository::Repository(const char* name, const char* url) : m_available_count(0) {
    // Initialize metadata
    (void)name; (void)url;
}

bool Repository::sync() {
    // In a real system, download index from m_metadata.url
    return true;
}

const PackageManifest* Repository::get_package(usize index) const {
    if (index < m_available_count) return &m_available[index];
    return nullptr;
}

} // namespace acos::pkg
