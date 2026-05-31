#pragma once
#include <acos/types.h>
#include "pkg.h"

namespace acos::pkg {

struct Dependency {
    char name[64];
    char version_constraint[32];
};

class DependencySolver {
public:
    DependencySolver();
    bool resolve(const PackageManifest& target, PackageManifest* result, usize* count);

private:
    bool check_conflicts();
    bool check_cycles();
};

} // namespace acos::pkg
