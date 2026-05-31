#include "package_manager.h"

namespace acos::pkg {

PackageManager::PackageManager() : m_repo_count(0) {}

PkgError PackageManager::install(const char* name) {
    (void)name;
    // 1. Find package in repositories
    // 2. Solve dependencies
    // 3. Download payloads
    // 4. Verify signatures
    // 5. Extract to VFS
    // 6. Update database
    return PkgError::Success;
}

PkgError PackageManager::remove(const char* name) {
    (void)name;
    return PkgError::Success;
}

PkgError PackageManager::upgrade(const char* name) {
    (void)name;
    return PkgError::Success;
}

PkgError PackageManager::verify(const char* name) {
    (void)name;
    return PkgError::Success;
}

} // namespace acos::pkg
