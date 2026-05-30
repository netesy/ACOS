#pragma once
#include <kernel/drivers/net/nic_driver.h>
#include <kernel/net/net_device.h>

namespace acos::drivers::net {

class VirtIONet : public NICDriver, public acos::net::NetDevice {
public:
    VirtIONet(u64 pci_base);

    bool initialize() override;
    bool probe(device::Device* dev) override;

    bool send_packet(const void* data, usize size) override;
    usize receive_packet(void* buffer, usize max_size) override;

    acos::net::MACAddress mac() const override { return m_mac; }
    u32 mtu() const override { return 1500; }

private:
    u64 m_pci_base;
    acos::net::MACAddress m_mac;
};

} // namespace acos::drivers::net
