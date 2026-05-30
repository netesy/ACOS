#include <kernel/vfs/path.h>
#include <acos/runtime.h>

namespace acos::vfs {

void Path::normalize(char* path) {
    if (!path) return;
    // Basic normalization: handle double slashes
    usize i = 0, j = 0;
    while (path[i]) {
        if (path[i] == '/' && path[i+1] == '/') {
            i++;
            continue;
        }
        path[j++] = path[i++];
    }
    path[j] = '\0';
}

bool Path::is_absolute(const char* path) {
    return path && path[0] == '/';
}

} // namespace acos::vfs
