#include "linux_errno.h"

namespace acos::compat::linux {

i32 translate_acos_to_linux_errno(u64 acos_error) {
    switch (acos_error) {
        case 0: return 0;
        case (u64)-1: return (i32)LinuxErrno::EPERM;
        case (u64)-2: return (i32)LinuxErrno::ENOENT;
        case (u64)-3: return (i32)LinuxErrno::EACCES;
        case (u64)-4: return (i32)LinuxErrno::ENOMEM;
        default: return (i32)LinuxErrno::EINVAL;
    }
}

} // namespace acos::compat::linux
