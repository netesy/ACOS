#pragma once
#include <kernel/vfs/vfs.h>
#include <kernel/vfs/console_node.h>
#include <kernel/hal/serial.h>
#include <kernel/memory/heap.h>

namespace acos::vfs {

class RamFileNode final : public Node {
public:
    RamFileNode() : m_size(0) {
        m_buffer = static_cast<char*>(memory::kmalloc(65536)); // 64KB buffer
        if (m_buffer) {
            memset(m_buffer, 0, 65536);
        }
    }
    ~RamFileNode() override {
        if (m_buffer) {
            memory::kfree(m_buffer);
        }
    }

    i32 read(u64 offset, usize size, void* buffer) override {
        if (!m_buffer || !buffer || offset >= m_size) return 0;
        usize readable = size;
        if (offset + readable > m_size) {
            readable = m_size - offset;
        }
        memcpy(buffer, m_buffer + offset, readable);
        return static_cast<i32>(readable);
    }

    i32 write(u64 offset, usize size, const void* buffer) override {
        if (!m_buffer || !buffer) return -1;
        if (offset + size > 65535) {
            if (offset >= 65535) return -1;
            size = 65535 - offset;
        }
        memcpy(m_buffer + offset, buffer, size);
        if (offset + size > m_size) {
            m_size = offset + size;
        }
        return static_cast<i32>(size);
    }

    u64 size() const override { return m_size; }
    NodeType type() const override { return NodeType::File; }
    i32 read_dir(u64, DirectoryEntry*, usize) override { return -1; }

    void truncate() {
        m_size = 0;
        if (m_buffer) {
            memset(m_buffer, 0, 65536);
        }
    }

private:
    char* m_buffer;
    u64 m_size;
};

class DevFileSystem : public FileSystem {
public:
    DevFileSystem() = default;
    ~DevFileSystem() override = default;

    Node* open(const char* path) override {
        acos::hal::serial_print("  DevFS: open path='");
        acos::hal::serial_print(path ? path : "null");
        acos::hal::serial_print("'\n");

        if (!path) return nullptr;

        const char* target1 = "/dev/console";
        const char* target2 = "console";
        bool match1 = true;
        for (int i = 0; target1[i] || path[i]; i++) {
            if (target1[i] != path[i]) {
                match1 = false;
                break;
            }
        }
        bool match2 = true;
        for (int i = 0; target2[i] || path[i]; i++) {
            if (target2[i] != path[i]) {
                match2 = false;
                break;
            }
        }
        if (match1 || match2) {
            acos::hal::serial_print("  DevFS: matched console!\n");
            return &m_console;
        }

        // Match pipe files and sub_out
        if (strcmp(path, "pipe_0") == 0 || strcmp(path, "dev/pipe_0") == 0 || strcmp(path, "/dev/pipe_0") == 0) {
            m_pipe0.truncate();
            return &m_pipe0;
        }
        if (strcmp(path, "pipe_1") == 0 || strcmp(path, "dev/pipe_1") == 0 || strcmp(path, "/dev/pipe_1") == 0) {
            m_pipe1.truncate();
            return &m_pipe1;
        }
        if (strcmp(path, "pipe_2") == 0 || strcmp(path, "dev/pipe_2") == 0 || strcmp(path, "/dev/pipe_2") == 0) {
            m_pipe2.truncate();
            return &m_pipe2;
        }
        if (strcmp(path, "sub_out") == 0 || strcmp(path, "dev/sub_out") == 0 || strcmp(path, "/dev/sub_out") == 0) {
            m_sub_out.truncate();
            return &m_sub_out;
        }

        acos::hal::serial_print("  DevFS: no match\n");
        return nullptr;
    }

    bool mount(const char* target) override {
        (void)target;
        return true;
    }

private:
    ConsoleNode m_console;
    RamFileNode m_pipe0;
    RamFileNode m_pipe1;
    RamFileNode m_pipe2;
    RamFileNode m_sub_out;
};

} // namespace acos::vfs
