#pragma once
#include <acos/types.h>

namespace acos::drivers::usb {

class XHCIController {
public:
    XHCIController(u64 bar0);
    bool initialize();

private:
    u64 m_bar0;
    volatile u32* m_regs;
    volatile u32* m_op_regs;
};

} // namespace acos::drivers::usb
