#include <kernel/device/tier1_driver.h>

namespace acos::device {

Tier1Driver::Tier1Driver(u64 process_id) : m_process_id(process_id), m_control_channel(nullptr) {}

bool Tier1Driver::initialize() {
    (void)m_control_channel;
    return true;
}

bool Tier1Driver::probe(Device* dev) {
    if (!dev) return false;
    return true;
}

} // namespace acos::device
