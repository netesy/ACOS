#include "xhci.h"
#include <kernel/memory/pmm.h>
#include <acos/runtime.h>

namespace acos::drivers::usb {

XHCIController::XHCIController(u64 bar0) : m_bar0(bar0), m_regs(reinterpret_cast<volatile u32*>(bar0)) {}

bool XHCIController::initialize() {
    if (!m_bar0) return false;

    u32 cap_length = m_regs[0] & 0xFF;
    m_op_regs = m_regs + (cap_length / 4);

    // 1. Reset controller
    m_op_regs[0] &= ~0x01; // Stop (R/S = 0)
    while (!(m_op_regs[1] & 0x01)); // Wait for HCHalted

    m_op_regs[0] |= 0x02; // HCRST = 1
    while (m_op_regs[0] & 0x02); // Wait for reset to complete

    // 2. Further initialization (Event Rings, DCBAA, etc.) would go here

    return true;
}

} // namespace acos::drivers::usb
