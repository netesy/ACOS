#include <acos/syscall.h>
#include <acos/ipc.h>
#include <acos/runtime.h>

using namespace acos;

extern "C" int main(int argc [[maybe_unused]], char** argv [[maybe_unused]]) {
    u64 pcie_channel = ipc::channel_create();
    if (!pcie_channel) return 1;

    if (!services::register_service("pcie_manager", pcie_channel)) return 2;

    while (true) {
        acos::ipc::Message msg;
        if (acos::ipc::channel_receive(pcie_channel, &msg, sizeof(msg))) {
            // PCI enumeration and device ownership logic
        }
    }
    return 0;
}
