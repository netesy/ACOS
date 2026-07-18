#pragma once
#include <kernel/vfs/vfs.h>
#include <kernel/vfs/console_node.h>
#include <kernel/hal/serial.h>

namespace acos::vfs {

class DevFileSystem : public FileSystem {
public:
    DevFileSystem() = default;
    ~DevFileSystem() override = default;

    Node* open(const char* path) override {
        acos::hal::serial_print("  DevFS: open path='");
        acos::hal::serial_print(path ? path : "null");
        acos::hal::serial_print("'\n");
        if (path) {
            acos::hal::serial_print("  DevFS: path hex: ");
            for (int i = 0; path[i]; i++) {
                acos::hal::serial_print_hex(path[i]);
                acos::hal::serial_print(" ");
            }
            acos::hal::serial_print("\n");
        }

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
        acos::hal::serial_print("  DevFS: no match\n");
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
