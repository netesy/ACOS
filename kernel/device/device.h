#pragma once
#include <acos/types.h>

namespace acos::device {

enum class DeviceType {
    Unknown,
    Bus,
    Storage,
    Network,
    Display,
    Input,
    Serial
};

class Device {
public:
    Device(u64 id, DeviceType type);
    virtual ~Device() = default;

    u64 id() const { return m_id; }
    DeviceType type() const { return m_type; }

private:
    u64 m_id;
    DeviceType m_type;
};

} // namespace acos::device
