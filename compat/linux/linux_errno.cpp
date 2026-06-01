#include "linux_errno.h"
namespace acos::compat::linux {
i32 translate_err(u64 e) { return (i32)e; }
}
