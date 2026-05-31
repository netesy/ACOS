#pragma once
#include <acos/types.h>
#include "pkg.h"

namespace acos::pkg {

struct InstalledPackage {
    PackageManifest manifest;
    char install_date[32];
    u64 install_size;
};

class PackageDatabase {
public:
    PackageDatabase();
    bool initialize();

    bool register_package(const Package& pkg);
    bool unregister_package(const char* name);

    bool is_installed(const char* name);
    const InstalledPackage* get_package(const char* name);

private:
    static constexpr usize MAX_INSTALLED = 1024;
    InstalledPackage m_installed[MAX_INSTALLED];
    usize m_count;
};

} // namespace acos::pkg
