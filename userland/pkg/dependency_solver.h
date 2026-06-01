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
    static constexpr usize MAX_VISITED = 32;

    bool check_conflicts() const;
    bool check_cycles() const;
    bool has_visited(const char* name) const;
    bool remember(const char* name);

    char m_visited[MAX_VISITED][64];
    usize m_visited_count;
};

} // namespace acos::pkg
