#include <acos/process.h>
#include <acos/runtime.h>
#include "package_manager.h"
#include "signature.h"

namespace acos::pkg {

namespace {

bool same_name(const char* lhs, const char* rhs) {
    if (!lhs || !rhs) {
        return false;
    }
    usize i = 0;
    while (lhs[i] && rhs[i] && lhs[i] == rhs[i]) {
        ++i;
    }
    return lhs[i] == rhs[i];
}

} // namespace

PackageManager::PackageManager() : m_repo_count(0) {
    m_db.initialize();
    for (usize i = 0; i < 16; ++i) {
        m_repos[i] = nullptr;
    }
}

PkgError PackageManager::install(const char* name) {
    if (!name || name[0] == '\0') return PkgError::IOError;

    const PackageManifest* manifest = nullptr;
    for (usize i = 0; i < m_repo_count && !manifest; ++i) {
        Repository* repo = m_repos[i];
        if (!repo) {
            continue;
        }
        for (usize j = 0; j < repo->package_count(); ++j) {
            const PackageManifest* candidate = repo->get_package(j);
            if (candidate && same_name(candidate->name, name)) {
                manifest = candidate;
                break;
            }
        }
    }

    if (!manifest) return PkgError::NotFound;

    PackageManifest deps[32];
    usize dep_count = 0;
    if (!m_solver.resolve(*manifest, deps, &dep_count)) {
        return PkgError::DependencyConflict;
    }

    // Repository manifests are trusted only after their dependency graph can be
    // resolved. Package payload verification is performed by Package::load() for
    // ACPK files before this installation path receives a manifest.
    Package pkg(*manifest);
    if (!m_db.register_package(pkg)) {
        return PkgError::IOError;
    }

    return PkgError::Success;
}

PkgError PackageManager::remove(const char* name) {
    if (!name || name[0] == '\0') return PkgError::IOError;

    if (!m_db.is_installed(name)) {
        return PkgError::NotFound;
    }

    if (!m_db.unregister_package(name)) {
        return PkgError::IOError;
    }

    return PkgError::Success;
}

PkgError PackageManager::upgrade(const char* name) {
    if (!name || name[0] == '\0') return PkgError::IOError;

    const InstalledPackage* installed = m_db.get_package(name);
    if (!installed) return PkgError::NotFound;

    return install(name);
}

PkgError PackageManager::verify(const char* name) {
    if (!name || name[0] == '\0') return PkgError::IOError;

    const InstalledPackage* pkg = m_db.get_package(name);
    if (!pkg) return PkgError::NotFound;

    PackageManifest deps[32];
    usize dep_count = 0;
    if (!m_solver.resolve(pkg->manifest, deps, &dep_count)) {
        return PkgError::DependencyConflict;
    }

    return PkgError::Success;
}

} // namespace acos::pkg
