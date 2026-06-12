#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/syscall.h>
#include <acos/ipc.h>
#include <acos/process.h>
#include <userland/shell/desktop_shell.h>

using namespace acos;
using namespace acos::shell;

extern "C" int main(int argc [[maybe_unused]], char** argv [[maybe_unused]]) {
    DesktopShell shell;
    shell.initialize();
    shell.run_loop();
    return 0;
}
