#pragma once
#include <acos/types.h>
#include "pkg.h"
#include "package_database.h"
#include "repository.h"
#include "dependency_solver.h"

namespace acos::pkg {

enum class PkgError {
    Success = 0,
    NotFound,
    DependencyConflict,
    SignatureInvalid,
    IOError,
    PermissionDenied
};

class PackageManager {
public:
    PackageManager();

    PkgError install(const char* name);
    PkgError remove(const char* name);
    PkgError upgrade(const char* name);
    PkgError verify(const char* name);

private:
    PackageDatabase m_db;
    DependencySolver m_solver;
    Repository* m_repos[16];
    usize m_repo_count;
};

} // namespace acos::pkg
