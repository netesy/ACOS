#include <acos/syscall.h>
#include <acos/ipc.h>
#include <acos/runtime.h>
#include "xhci.h"

using namespace acos;

extern "C" int main(int argc [[maybe_unused]], char** argv [[maybe_unused]]) {
    u64 xhci_channel = ipc::channel_create();
    if (!xhci_channel) return 1;

    if (!services::register_service("xhci_driver", xhci_channel)) return 2;

    while (true) {
        acos::ipc::Message msg;
        if (acos::ipc::channel_receive(xhci_channel, &msg, sizeof(msg))) {
        }
    }
    return 0;
}
