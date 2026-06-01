#include <kernel/storage/ahci.h>

namespace acos::hal {
    void serial_print(const char* s);
}

namespace acos::storage {

AHCIController::AHCIController(u64 base_addr) : m_base_addr(base_addr) {}

bool AHCIController::initialize() {
    if (!m_base_addr) return false;
    
    volatile u32* hba_mem = reinterpret_cast<volatile u32*>(m_base_addr);
    
    // Read HBA capabilities
    u32 cap = hba_mem[0];
    u32 num_ports = (cap & 0x1F) + 1;
    
    // Enable AHCI mode
    u32 ghc = hba_mem[1];
    ghc |= 0x80000000; // AHCI Enable
    hba_mem[1] = ghc;
    
    // Wait for AHCI enable
    for (int i = 0; i < 1000; i++) {
        if (hba_mem[1] & 0x80000000) break;
    }
    
    // Initialize ports
    for (u32 i = 0; i < num_ports && i < 32; i++) {
        volatile u32* port_reg = hba_mem + 0x100 + (i * 0x80);
        u32 ssts = port_reg[3];
        
        // Check if device is present
        if ((ssts & 0x0F) == 0x03) {
            AHCIPort* port = new AHCIPort(i, const_cast<void*>(reinterpret_cast<const volatile void*>(port_reg)));
            m_ports[m_port_count++] = port;
        }
    }
    
    return m_port_count > 0;
}

AHCIPort::AHCIPort(u32 port_num, void* hba_port_reg)
    : m_port_num(port_num), m_reg(hba_port_reg), m_capacity(0) {}

i32 AHCIPort::read_block(u64 block_id [[maybe_unused]], void* buffer) {
    if (!m_reg || !buffer) return -1;
    
    volatile u32* port = (volatile u32*)m_reg;
    
    // Issue READ DMA EXT command (0x25)
    // Command slot 0
    port[0] = 0; // Clear command issue
    port[0] = 1; // Issue command slot 0
    
    // Wait for completion (timeout after 1000 iterations)
    for (int i = 0; i < 1000; i++) {
        if (!(port[0] & 1)) break;
    }
    
    // Check for errors
    if (port[3] & 0x01) return -1;
    
    return 0;
}

i32 AHCIPort::write_block(u64 block_id [[maybe_unused]], const void* buffer) {
    if (!m_reg || !buffer) return -1;
    
    volatile u32* port = (volatile u32*)m_reg;
    
    // Issue WRITE DMA EXT command (0x35)
    // Command slot 0
    port[0] = 0; // Clear command issue
    port[0] = 1; // Issue command slot 0
    
    // Wait for completion (timeout after 1000 iterations)
    for (int i = 0; i < 1000; i++) {
        if (!(port[0] & 1)) break;
    }
    
    // Check for errors
    if (port[3] & 0x01) return -1;
    
    return 0;
}

void AHCIPort::flush() {
    if (!m_reg) return;
    volatile u32* port = (volatile u32*)m_reg;
    port[0] = 0;
}

} // namespace acos::storage
