#include <kernel/storage/partition.h>
#include <kernel/storage/storage_manager.h>
#include <kernel/storage/filesystem_manager.h>
#include <kernel/hal/serial.h>

namespace acos::storage {

namespace {

bool guid_equal(const u8* g1, const u8* g2) {
    for (int i = 0; i < 16; i++) {
        if (g1[i] != g2[i]) return false;
    }
    return true;
}

// EFI System Partition (ESP) GUID: 28 73 2A C1 1F F8 D2 11 BA 4B 00 A0 C9 3E C9 3B
const u8 ESP_GUID[16] = {
    0x28, 0x73, 0x2A, 0xC1, 0x1F, 0xF8, 0xD2, 0x11,
    0xBA, 0x4B, 0x00, 0xA0, 0xC9, 0x3E, 0xC9, 0x3B
};

// Custom ASFS System Partition GUID: 53 41 A5 A5 53 46 53 4F A5 A5 A5 A5 A5 A5 A5 A5
const u8 ASFS_GUID[16] = {
    0x53, 0x41, 0xA5, 0xA5, 0x53, 0x46, 0x53, 0x4F,
    0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5
};

} // namespace

Partition::Partition(BlockDevice* parent, u64 start_lba, u64 sector_count)
    : m_parent(parent), m_start_lba(start_lba), m_sector_count(sector_count) {}

i32 Partition::read_block(u64 block_id, void* buffer) {
    if (block_id >= m_sector_count) return -1;
    return m_parent->read_block(m_start_lba + block_id, buffer);
}

i32 Partition::write_block(u64 block_id, const void* buffer) {
    if (block_id >= m_sector_count) return -1;
    return m_parent->write_block(m_start_lba + block_id, buffer);
}

void Partition::flush() { m_parent->flush(); }

void PartitionManager::enumerate(BlockDevice* device) {
    if (!device) return;

    u8 sector_buf[512];

    // 1. Try to read GPT Header at LBA 1 first
    if (device->read_block(1, sector_buf) == 0) {
        GPTHeader* gpt = (GPTHeader*)sector_buf;
        if (gpt->signature == 0x5452415020494645ULL) { // "EFI PART"
            hal::serial_print("PartitionManager: GPT Signature Matched on device!\n");

            u64 entries_lba = gpt->partition_entries_lba;
            u32 entry_count = gpt->num_partition_entries;
            u32 entry_size = gpt->partition_entry_size;

            hal::serial_print("PartitionManager: Parsing GPT Entries count=");
            hal::serial_print_hex(entry_count);
            hal::serial_print(" starting LBA=");
            hal::serial_print_hex(entries_lba);
            hal::serial_print("\n");

            // Avoid division by zero and sanity limits
            if (entry_size > 0 && entry_count > 0 && entry_count <= 256) {
                u32 entries_per_sector = 512 / entry_size;
                u8 entries_sector_buf[512];
                u32 entries_parsed = 0;

                for (u64 current_sector = entries_lba; entries_parsed < entry_count; current_sector++) {
                    if (device->read_block(current_sector, entries_sector_buf) != 0) {
                        break;
                    }

                    for (u32 i = 0; i < entries_per_sector && entries_parsed < entry_count; i++) {
                        GPTPartitionEntry* entry = (GPTPartitionEntry*)(entries_sector_buf + (i * entry_size));
                        entries_parsed++;

                        // Check if entry is active/used
                        bool all_zero = true;
                        for (int j = 0; j < 16; j++) {
                            if (entry->type_guid[j] != 0) {
                                all_zero = false;
                                break;
                            }
                        }
                        if (all_zero) continue;

                        u64 start = entry->starting_lba;
                        u64 end = entry->ending_lba;
                        if (end < start || start >= device->block_count()) continue;
                        u64 count = end - start + 1;

                        Partition* part = new Partition(device, start, count);
                        if (part) {
                            StorageManager::register_device(0x200 + entries_parsed, part);

                            // Check Partition GUID to determine appropriate VFS mount target path
                            if (guid_equal(entry->type_guid, ESP_GUID)) {
                                hal::serial_print("PartitionManager: Found GPT EFI System Partition (ESP) at LBA: ");
                                hal::serial_print_hex(start);
                                hal::serial_print("\n");
                                FileSystemManager::probe_and_mount(part, "/");
                            } else if (guid_equal(entry->type_guid, ASFS_GUID)) {
                                hal::serial_print("PartitionManager: Found GPT ASFS Partition at LBA: ");
                                hal::serial_print_hex(start);
                                hal::serial_print("\n");
                                FileSystemManager::probe_and_mount(part, "/system");
                            } else {
                                // Default fallback probe and mount
                                FileSystemManager::probe_and_mount(part, "/");
                            }
                        }
                    }
                }
                return; // Succesfully parsed GPT, skip MBR fallback
            }
        }
    }

    // 2. MBR Fallback
    if (device->read_block(0, sector_buf) != 0) return;
    
    // Always probe the device itself first
    FileSystemManager::probe_and_mount(device, "/");

    if (sector_buf[510] == 0x55 && sector_buf[511] == 0xAA) {
        hal::serial_print("PartitionManager: MBR Signature Matched. Enumerating partitions...\n");
        for (int i = 0; i < 4; i++) {
            u8* entry = sector_buf + 446 + (i * 16);
            u8 type = entry[4];
            if (type == 0) continue;
            u32 start_lba = *(u32*)(entry + 8);
            u32 sector_count = *(u32*)(entry + 12);
            if (sector_count == 0) continue;

            Partition* part = new Partition(device, start_lba, sector_count);
            if (part) {
                StorageManager::register_device(0x100 + i, part);
                if (type == 0xAC) {
                    hal::serial_print("PartitionManager: Found MBR ASFS Partition at LBA: ");
                    hal::serial_print_hex(start_lba);
                    hal::serial_print("\n");
                    FileSystemManager::probe_and_mount(part, "/system");
                } else {
                    FileSystemManager::probe_and_mount(part, "/");
                }
            }
        }
    }
}

} // namespace acos::storage
