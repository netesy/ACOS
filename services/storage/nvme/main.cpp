#include <acos/syscall.h>
#include <acos/ipc.h>
#include <acos/runtime.h>
#include "nvme.h"

using namespace acos;

extern "C" int main(int argc [[maybe_unused]], char** argv [[maybe_unused]]) {
    u64 nvme_channel = ipc::channel_create();
    if (!nvme_channel) return 1;

    if (!services::register_service("nvme_driver", nvme_channel)) return 2;

    // Discovery via pcie_manager would happen here.
    // For now, it's a foundation stub.

    while (true) {
        acos::ipc::Message msg;
        if (acos::ipc::channel_receive(nvme_channel, &msg, sizeof(msg))) {
        }
    }
    return 0;
}
