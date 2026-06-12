#include <acos/process.h>
#include <acos/runtime.h>
#include <errno.h>
#include <acos/types.h>

extern "C" {
    int acos_errno = 0;
}

namespace acos::posix {

int translate_error(acos::u64 acos_error) {
    switch (acos_error) {
        case 0: return 0;
        case (acos::u64)-1: return EACCES;
        case (acos::u64)-2: return ENOENT;
        default: return EINVAL;
    }
}

} // namespace acos::posix
