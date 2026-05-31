#pragma once
#include <acos/types.h>
#include "pkg.h"

namespace acos::pkg {

struct RepositoryMetadata {
    char name[64];
    char url[256];
    u32 priority;
};

class Repository {
public:
    Repository(const char* name, const char* url);
    bool sync();

    const RepositoryMetadata& metadata() const { return m_metadata; }

    usize package_count() const { return m_available_count; }
    const PackageManifest* get_package(usize index) const;

private:
    RepositoryMetadata m_metadata;
    static constexpr usize MAX_PACKAGES = 4096;
    PackageManifest m_available[MAX_PACKAGES];
    usize m_available_count;
};

} // namespace acos::pkg
