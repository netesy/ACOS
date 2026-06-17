#include "nvme.h"
#include <acos/syscall.h>
#include <acos/runtime.h>

namespace acos::drivers::storage {

NVMeController::NVMeController(u64 bar0) : m_bar0(bar0), m_regs(reinterpret_cast<volatile u32*>(bar0)) {}

bool NVMeController::initialize() {
    if (!m_bar0) return false;

    // 1. Wait for controller ready
    // CAP.RDY might need to be checked, but for simplicity:
    u32 config = m_regs[0x14/4]; // CC
    if (config & 0x01) { // Enabled?
        m_regs[0x14/4] &= ~0x01; // Disable
    }

    // 2. Setup Admin Queue
    m_admin_queue.size = 64;
    // Syscall to allocate physically contiguous memory (DMA)
    m_admin_queue.sq_virt = reinterpret_cast<void*>(acos::syscall(acos::sys::SyscallNum::MemoryAllocateContiguous, 1));
    m_admin_queue.cq_virt = reinterpret_cast<void*>(acos::syscall(acos::sys::SyscallNum::MemoryAllocateContiguous, 1));
    memset(m_admin_queue.sq_virt, 0, 4096);
    memset(m_admin_queue.cq_virt, 0, 4096);

    m_regs[0x28/4] = (u32)(u64)m_admin_queue.sq_virt; // ASQ
    m_regs[0x2C/4] = (u32)((u64)m_admin_queue.sq_virt >> 32);
    m_regs[0x30/4] = (u32)(u64)m_admin_queue.cq_virt; // ACQ
    m_regs[0x34/4] = (u32)((u64)m_admin_queue.cq_virt >> 32);
    m_regs[0x24/4] = ((m_admin_queue.size - 1) << 16) | (m_admin_queue.size - 1); // AQA

    // 3. Enable controller
    m_regs[0x14/4] |= 0x01; // EN=1

    return true;
}

i32 NVMeController::read_block(u64 block_id, void* buffer) {
    // Simplified stub for modern hardware readiness
    (void)block_id; (void)buffer;
    return 0;
}

i32 NVMeController::write_block(u64 block_id, const void* buffer) {
    (void)block_id; (void)buffer;
    return 0;
}

void NVMeController::flush() {}

} // namespace acos::drivers::storage
