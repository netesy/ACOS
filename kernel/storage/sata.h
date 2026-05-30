#pragma once
#include <acos/types.h>

namespace acos::storage {

struct SATAIdentData {
    u16 config;
    u16 cylinders;
    u16 reserved;
    u16 heads;
    // ... many more fields
    u16 serial[10];
    u16 fw_rev[4];
    u16 model[20];
    u32 max_lba_low;
    u32 max_lba_high;
};

} // namespace acos::storage
