#include <kernel/storage/ahci.h>

namespace acos::hal {
    void serial_print(const char* s);
}

namespace acos::storage {

AHCIController::AHCIController(u64 base_addr) : m_base_addr(base_addr) {}

bool AHCIController::initialize() {
    return true;
}

AHCIPort::AHCIPort(u32 port_num, void* hba_port_reg)
    : m_port_num(port_num), m_reg(hba_port_reg), m_capacity(0) {}

i32 AHCIPort::read_block(u64 block_id, void* buffer) {
    (void)block_id; (void)buffer;
    return 0;
}

i32 AHCIPort::write_block(u64 block_id, const void* buffer) {
    (void)block_id; (void)buffer;
    return 0;
}

void AHCIPort::flush() {}

} // namespace acos::storage
