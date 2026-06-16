#pragma once
#include <acos/types.h>
#include <kernel/storage/block_device.h>

namespace acos::storage {

// Forward declaration
class AHCIPort;

/**
 * AHCI Controller driver foundation.
 * Manages HBA (Host Bus Adapter) ports and communication.
 */
class AHCIController {
public:
    AHCIController(u64 base_addr);
    bool initialize();

    u32 port_count() const { return m_port_count; }
    AHCIPort* get_port(u32 index) const { return index < m_port_count ? m_ports[index] : nullptr; }

    // Future: Interrupt handling
private:
    u64 m_base_addr;
    AHCIPort* m_ports[32];
    u32 m_port_count = 0;
};

class AHCIPort : public BlockDevice {
public:
    AHCIPort(u32 port_num, void* hba_port_reg);

    void configure();

    i32 read_block(u64 block_id, void* buffer) override;
    i32 write_block(u64 block_id, const void* buffer) override;
    void flush() override;
    usize block_size() const override { return 512; }
    u64 capacity() const override { return m_capacity; }

private:
    int find_cmd_slot();
    [[maybe_unused]] u32 m_port_num;
    void* m_reg;
    u64 m_capacity;
    u64 m_ctba[32];
};

} // namespace acos::storage
