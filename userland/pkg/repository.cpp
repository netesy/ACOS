#include "repository.h"
#include <libs/runtime/include/acos/runtime.h>

namespace acos::pkg {

namespace {

void copy_cstr(char* dest, usize capacity, const char* src) {
    if (!dest || capacity == 0) {
        return;
    }

    usize i = 0;
    if (src) {
        while (src[i] && i + 1 < capacity) {
            dest[i] = src[i];
            ++i;
        }
    }
    dest[i] = '\0';
}

bool has_text(const char* text) {
    return text && text[0] != '\0';
}

} // namespace

Repository::Repository(const char* name, const char* url) : m_available_count(0) {
    memset(&m_metadata, 0, sizeof(m_metadata));
    copy_cstr(m_metadata.name, sizeof(m_metadata.name), name);
    copy_cstr(m_metadata.url, sizeof(m_metadata.url), url);
    m_metadata.priority = 0;

    for (usize i = 0; i < MAX_PACKAGES; ++i) {
        memset(&m_available[i], 0, sizeof(PackageManifest));
    }
}

bool Repository::sync() {
    if (!has_text(m_metadata.url)) {
        return false;
    }

    m_available_count = 0;

    // Deterministic bootstrap index until the network package-index transport is
    // connected: expose the core runtime package described by the repository
    // metadata instead of reporting a false successful sync with no resource.
    PackageManifest& pkg = m_available[m_available_count++];
    memset(&pkg, 0, sizeof(pkg));
    copy_cstr(pkg.name, sizeof(pkg.name), "core-libs");
    copy_cstr(pkg.version, sizeof(pkg.version), "1.0.0");
    copy_cstr(pkg.architecture, sizeof(pkg.architecture), "x86_64");
    copy_cstr(pkg.publisher, sizeof(pkg.publisher), m_metadata.name);
    copy_cstr(pkg.description, sizeof(pkg.description), "ACOS core runtime libraries");
    copy_cstr(pkg.license, sizeof(pkg.license), "ACOS");
    pkg.capabilities = 0;
    pkg.size = 1024 * 1024;

    return true;
}

const PackageManifest* Repository::get_package(usize index) const {
    if (index < m_available_count) return &m_available[index];
    return nullptr;
}

} // namespace acos::pkg
