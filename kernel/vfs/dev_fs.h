#pragma once
#include <kernel/vfs/vfs.h>
#include <kernel/vfs/console_node.h>

namespace acos::vfs {

class DevFileSystem : public FileSystem {
public:
    DevFileSystem() = default;
    ~DevFileSystem() override = default;

    Node* open(const char* path) override {
        // Simple matching for /dev/console
        // The path passed to fs->open is the full path usually.
        // VFS::open passes the full path.
        const char* target = "/dev/console";
        bool match = true;
        for (int i = 0; target[i] || path[i]; i++) {
            if (target[i] != path[i]) {
                match = false;
                break;
            }
        }
        if (match) {
            return &m_console;
        }
        return nullptr;
    }

    bool mount(const char* target) override {
        (void)target;
        return true;
    }

private:
    ConsoleNode m_console;
};

} // namespace acos::vfs
