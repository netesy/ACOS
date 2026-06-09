#pragma once
#include <kernel/vfs/vfs.h>

namespace acos::vfs {

class ConsoleNode : public Node {
public:
    ConsoleNode() = default;
    ~ConsoleNode() override = default;

    i32 read(u64 offset, usize size, void* buffer) override;
    i32 write(u64 offset, usize size, const void* buffer) override;
    u64 size() const override { return 0; }
    NodeType type() const override { return NodeType::Device; }
};

} // namespace acos::vfs
