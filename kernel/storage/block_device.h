#pragma once
#include <acos/types.h>

namespace acos::storage {

class BlockDevice {
public:
    virtual ~BlockDevice() = default;
    virtual i32 read_block(u64 block_id, void* buffer) = 0;
    virtual i32 write_block(u64 block_id, const void* buffer) = 0;
    virtual void flush() = 0;
    virtual usize block_size() const = 0;
    virtual u64 capacity() const = 0;
};

} // namespace acos::storage
