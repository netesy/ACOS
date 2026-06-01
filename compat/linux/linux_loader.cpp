#include "linux_loader.h"
#include <kernel/vfs/vfs.h>
namespace acos::compat::linux {
bool LinuxLoader::load_linux_binary(const char* path) { (void)path; return true; }
}
