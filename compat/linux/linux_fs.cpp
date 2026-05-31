#include "linux_fs.h"
#include <libs/runtime/include/acos/runtime.h>

namespace acos::compat::linux {

u64 LinuxFS::translate_path(const char* linux_path, char* acos_path) {
    if (!linux_path || !acos_path) return (u64)-1;

    // Simple mapping logic
    // /proc -> /system/proc
    // /dev -> /system/dev
    // /tmp -> /system/tmp

    usize i = 0;
    const char* prefix = "/system";
    while (prefix[i]) {
        acos_path[i] = prefix[i];
        i++;
    }

    usize j = 0;
    while (linux_path[j] && i < 255) {
        acos_path[i++] = linux_path[j++];
    }
    acos_path[i] = '\0';

    return 0;
}

} // namespace acos::compat::linux
