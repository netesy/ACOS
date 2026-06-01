#include "linux_fs.h"

namespace acos::compat::linux {

namespace {

void copy_path(char* dst, const char* src) {
    if (!dst) return;
    usize i = 0;
    while (src && src[i] && i < 255) {
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
}

bool starts_with(const char* s, const char* prefix) {
    if (!s || !prefix) return false;
    for (usize i = 0; prefix[i]; ++i) {
        if (s[i] != prefix[i]) return false;
    }
    return true;
}

} // namespace

u64 LinuxFS::translate(const char* linux_path, char* acos_path) {
    if (!linux_path || !acos_path) return static_cast<u64>(-1);

    if (starts_with(linux_path, "/proc") || starts_with(linux_path, "/sys")) {
        return static_cast<u64>(-1);
    }
    if (starts_with(linux_path, "/dev/")) {
        copy_path(acos_path, linux_path);
        return 0;
    }
    if (starts_with(linux_path, "/tmp")) {
        copy_path(acos_path, "/ram/tmp");
        return 0;
    }

    copy_path(acos_path, linux_path);
    return 0;
}

} // namespace acos::compat::linux
