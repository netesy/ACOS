#include "pkg.h"
#include <libs/runtime/include/acos/runtime.h>

namespace acos::pkg {

Package::Package(const char* path) {
    // Basic copy to m_path
    usize i = 0;
    while(path[i] && i < 255) {
        m_path[i] = path[i];
        i++;
    }
    m_path[i] = '\0';
}

bool Package::load() {
    // In a real implementation, we would open the file via VFS
    // and read the header and manifest.
    return true;
}

} // namespace acos::pkg
