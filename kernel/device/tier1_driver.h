#pragma once
#include <kernel/device/driver.h>
#include <kernel/ipc/channel.h>

namespace acos::device {

class Tier1Driver : public Driver {
public:
    Tier1Driver(u64 process_id);

    bool initialize() override;
    bool probe(Device* dev) override;

    u64 process_id() const { return m_process_id; }

private:
    u64 m_process_id;
    ipc::Channel* m_control_channel;
};

} // namespace acos::device
