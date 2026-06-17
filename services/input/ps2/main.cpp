#include <acos/syscall.h>
#include <acos/ipc.h>
#include <acos/runtime.h>
#include "ps2.h"

using namespace acos;

extern "C" int main(int argc [[maybe_unused]], char** argv [[maybe_unused]]) {
    u64 ps2_channel = ipc::channel_create();
    if (!ps2_channel) return 1;

    if (!services::register_service("ps2_driver", ps2_channel)) return 2;

    while (true) {
        acos::ipc::Message msg;
        if (acos::ipc::channel_receive(ps2_channel, &msg, sizeof(msg))) {
        }
    }
    return 0;
}
