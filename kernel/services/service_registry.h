#pragma once
#include <acos/types.h>
#include <kernel/ipc/channel.h>

namespace acos::services {

static constexpr usize MAX_SERVICES = 64;
static constexpr usize MAX_NAME_LEN = 32;

struct ServiceEntry {
    char name[MAX_NAME_LEN];
    ipc::Channel* channel;
    u64 owner_pid;
};

void init();
bool register_service(const char* name, ipc::Channel* channel, u64 pid);
ipc::Channel* locate_service(const char* name);

} // namespace acos::services
