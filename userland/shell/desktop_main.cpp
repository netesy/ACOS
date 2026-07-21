#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/syscall.h>
#include <acos/ipc.h>
#include <acos/process.h>
#include <userland/shell/desktop_shell.h>

using namespace acos;
using namespace acos::shell;

#include <acos/vfs.h>

extern "C" int main(int argc [[maybe_unused]], char** argv [[maybe_unused]]) {
    i32 fd = acos::vfs::open("/dev/console", 0);
    if (fd >= 0) {
        acos::vfs::dup2(fd, 0);
        acos::vfs::dup2(fd, 1);
        acos::vfs::dup2(fd, 2);
        acos::vfs::close(fd);
    }

    DesktopShell shell;
    shell.initialize();
    shell.run_loop();
    return 0;
}
