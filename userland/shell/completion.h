#pragma once
#include <acos/types.h>

namespace acos::shell {

class CompletionManager {
public:
    static int complete(const char* current_cwd, const char* partial, char* out_completed, bool& out_is_dir);
};

} // namespace acos::shell
