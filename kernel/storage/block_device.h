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

    // Production-ready multiple blocks read/write extensions
    virtual i32 read_blocks(u64 block_id, u64 count, void* buffer) {
        u8* ptr = reinterpret_cast<u8*>(buffer);
        for (u64 i = 0; i < count; ++i) {
            // Guard against overflow during address math
            if (read_block(block_id + i, ptr + i * block_size()) != 0) {
                return -1;
            }
        }
        return 0;
    }

    virtual i32 write_blocks(u64 block_id, u64 count, const void* buffer) {
        if (is_read_only()) return -1;
        const u8* ptr = reinterpret_cast<const u8*>(buffer);
        for (u64 i = 0; i < count; ++i) {
            if (write_block(block_id + i, ptr + i * block_size()) != 0) {
                return -1;
            }
        }
        return 0;
    }

    virtual u64 block_count() const {
        usize size = block_size();
        return size > 0 ? (capacity() / size) : 0;
    }

    virtual bool is_read_only() const {
        return false;
    }
};

} // namespace acos::storage
