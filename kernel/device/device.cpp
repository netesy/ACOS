#include <kernel/device/device.h>

namespace acos::device {

Device::Device(u64 id, DeviceType type) : m_id(id), m_type(type) {}

} // namespace acos::device
