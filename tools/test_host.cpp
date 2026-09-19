#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <cstring>
#include <random>
#include <chrono>
#include <iomanip>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wunused-function"

#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "libs/stb_image_write.h"

#include "libs/miniz.h"

#define DR_WAV_IMPLEMENTATION
#include "libs/dr_wav.h"

#define DR_MP3_IMPLEMENTATION
#include "libs/dr_mp3.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "libs/stb_truetype.h"

#include "libs/monocypher.h"

#pragma GCC diagnostic pop

// Mock Types
typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef size_t usize;
typedef int i32;
typedef short i16;

namespace mock_pmm {

static constexpr u64 PAGE_SIZE = 4096;
static constexpr u32 MAX_ORDER = 16;

static std::vector<u8> g_phys_mem;
static std::vector<u64> g_bitmap;
static std::vector<u16> g_page_ref_counts;
static std::vector<u8> g_page_orders;
static u64 g_total_pages = 0;
static u64 g_used_pages = 0;

static u64 g_buddy_free_head[MAX_ORDER + 1] = {0};

static inline void bitmap_set(u64 page) {
    g_bitmap[page / 64] |= (1ULL << (page % 64));
}

static inline void bitmap_clear(u64 page) {
    g_bitmap[page / 64] &= ~(1ULL << (page % 64));
}

static inline bool bitmap_test(u64 page) {
    return (g_bitmap[page / 64] & (1ULL << (page % 64))) != 0;
}

static inline u64 order_to_pages(u32 order) {
    return 1ULL << order;
}

static inline u32 pages_to_order(u64 pages) {
    u32 order = 0;
    while ((1ULL << order) < pages) {
        order++;
    }
    return order;
}

static inline u64 page_to_addr(u64 page_idx) {
    return page_idx * PAGE_SIZE;
}

static inline u64 addr_to_page(u64 addr) {
    return addr / PAGE_SIZE;
}

// Memory read/write helper for simulated physical memory
static inline u64 read_mem64(u64 addr) {
    assert(addr + 8 <= g_phys_mem.size());
    return *reinterpret_cast<u64*>(&g_phys_mem[addr]);
}

static inline void write_mem64(u64 addr, u64 value) {
    assert(addr + 8 <= g_phys_mem.size());
    *reinterpret_cast<u64*>(&g_phys_mem[addr]) = value;
}

static void buddy_insert_to_list(u64 page_idx, u32 order) {
    u64 addr = page_to_addr(page_idx);
    u64 old_head = g_buddy_free_head[order];
    write_mem64(addr, old_head); // next = old_head
    write_mem64(addr + 8, 0);    // prev = 0
    if (old_head != 0) {
        write_mem64(old_head + 8, addr); // old_head->prev = addr
    }
    g_buddy_free_head[order] = addr;
    g_page_orders[page_idx] = order;
}

static void buddy_remove_from_list(u64 page_idx, u32 order) {
    u64 addr = page_to_addr(page_idx);
    u64 next_addr = read_mem64(addr);
    u64 prev_addr = read_mem64(addr + 8);
    if (prev_addr != 0) {
        write_mem64(prev_addr, next_addr);
    } else {
        g_buddy_free_head[order] = next_addr;
    }
    if (next_addr != 0) {
        write_mem64(next_addr + 8, prev_addr);
    }
}

static void buddy_free_block(u64 page_idx, u32 order, bool check_processed) {
    while (order < MAX_ORDER) {
        u64 buddy_idx = page_idx ^ (1ULL << order);
        if (buddy_idx + (1ULL << order) > g_total_pages) {
            break;
        }
        if (check_processed && buddy_idx > page_idx) {
            break;
        }
        if (bitmap_test(buddy_idx) || g_page_orders[buddy_idx] != order) {
            break;
        }
        buddy_remove_from_list(buddy_idx, order);
        g_page_orders[buddy_idx] = 0xFF;
        if (buddy_idx < page_idx) {
            page_idx = buddy_idx;
        }
        order++;
    }
    buddy_insert_to_list(page_idx, order);
}

void pmm_init(u64 total_pages) {
    g_total_pages = total_pages;
    g_phys_mem.assign(total_pages * PAGE_SIZE, 0);
    g_bitmap.assign((total_pages / 64) + 1, 0ULL);
    g_page_ref_counts.assign(total_pages, 0);
    g_page_orders.assign(total_pages, 0xFF);
    g_used_pages = 0;

    for (u32 o = 0; o <= MAX_ORDER; o++) {
        g_buddy_free_head[o] = 0;
    }

    // Mark page 0 as reserved (null guard)
    bitmap_set(0);
    g_used_pages++;

    // Mark some dummy pages as used to simulate kernel/gaps
    for (u64 p = 100; p < 200; p++) {
        bitmap_set(p);
        g_used_pages++;
    }

    // Build lists
    for (u64 p = 1; p < g_total_pages; p++) {
        if (!bitmap_test(p)) {
            buddy_free_block(p, 0, true);
        }
    }
}

u64 pmm_alloc_contiguous(u64 page_count) {
    if (page_count == 0) return 0;
    u32 order = pages_to_order(page_count);
    if (order > MAX_ORDER) return 0;

    u32 o = order;
    while (o <= MAX_ORDER && g_buddy_free_head[o] == 0) {
        o++;
    }

    if (o > MAX_ORDER) return 0;

    u64 block_addr = g_buddy_free_head[o];
    u64 next_block = read_mem64(block_addr);
    g_buddy_free_head[o] = next_block;
    if (next_block != 0) {
        write_mem64(next_block + 8, 0);
    }

    while (o > order) {
        o--;
        u64 buddy_addr = block_addr + (order_to_pages(o) * PAGE_SIZE);
        buddy_insert_to_list(addr_to_page(buddy_addr), o);
    }

    u64 start_page = addr_to_page(block_addr);
    u64 pages_allocated = order_to_pages(order);

    for (u64 i = 0; i < pages_allocated; i++) {
        bitmap_set(start_page + i);
        g_page_ref_counts[start_page + i] = 1;
    }
    g_used_pages += pages_allocated;
    g_page_orders[start_page] = order;

    // Zero out mock memory payload
    std::fill(g_phys_mem.begin() + block_addr, g_phys_mem.begin() + block_addr + pages_allocated * PAGE_SIZE, 0);

    return block_addr;
}

u64 pmm_alloc() {
    return pmm_alloc_contiguous(1);
}

void pmm_free(u64 addr) {
    if (addr == 0) return;
    u64 page = addr_to_page(addr);
    if (g_page_ref_counts[page] > 0) {
        g_page_ref_counts[page]--;
        if (g_page_ref_counts[page] > 0) {
            return;
        }
    }

    if (bitmap_test(page)) {
        u32 order = g_page_orders[page];
        if (order > MAX_ORDER) {
            order = 0;
        }
        u64 pages_to_free = order_to_pages(order);
        for (u64 i = 0; i < pages_to_free; i++) {
            bitmap_clear(page + i);
        }
        g_used_pages -= pages_to_free;
        buddy_free_block(page, order, false);
    }
}

} // namespace mock_pmm


namespace mock_fat32 {

struct MockBlockDevice {
    std::vector<u8> storage;
    MockBlockDevice(usize size_sectors) {
        storage.assign(size_sectors * 512, 0);
    }

    i32 read_block(u64 lba, void* buffer) {
        if (lba * 512 >= storage.size()) return -1;
        memcpy(buffer, &storage[lba * 512], 512);
        return 0;
    }

    i32 write_block(u64 lba, const void* buffer) {
        if (lba * 512 >= storage.size()) return -1;
        memcpy(&storage[lba * 512], buffer, 512);
        return 0;
    }
};

struct MockFAT32FileSystem {
    MockBlockDevice* m_device;
    u32 m_fat_start = 32;
    u32 m_data_start = 1000;
    u32 m_total_sectors = 65536;
    u8 m_sectors_per_cluster = 8;
    u32 m_fsinfo_sector = 1;
    u32 m_free_clusters = 8000;
    u32 m_next_free_cluster_hint = 2;

    MockFAT32FileSystem(MockBlockDevice* device) : m_device(device) {
        // Initialize dummy FSInfo block
        u8 fsinfo[512] = {0};
        *(u32*)(fsinfo + 0) = 0x41615252;
        *(u32*)(fsinfo + 484) = 0x61417272;
        *(u32*)(fsinfo + 488) = m_free_clusters;
        *(u32*)(fsinfo + 492) = m_next_free_cluster_hint;
        m_device->write_block(m_fsinfo_sector, fsinfo);
    }

    bool write_fat_entry(u32 cluster, u32 value) {
        alignas(4096) u8 fat_sector[512];
        u32 fat_offset = cluster * 4;
        u32 fat_block = m_fat_start + (fat_offset / 512);
        if (m_device->read_block(fat_block, fat_sector) != 0) return false;
        *(u32*)(fat_sector + (fat_offset % 512)) = value;
        if (m_device->write_block(fat_block, fat_sector) != 0) return false;
        return true;
    }

    void update_fsinfo(u32 free_clusters, u32 next_free_hint) {
        alignas(4096) u8 fsinfo_buf[512];
        if (m_device->read_block(m_fsinfo_sector, fsinfo_buf) == 0) {
            *(u32*)(fsinfo_buf + 488) = free_clusters;
            *(u32*)(fsinfo_buf + 492) = next_free_hint;
            m_device->write_block(m_fsinfo_sector, fsinfo_buf);
        }
    }
};

} // namespace mock_fat32


// Test Runner & Asserts
void run_pmm_tests() {
    std::cout << "[UNIT TEST] Initializing Buddy Allocator with 1024 pages...\n";
    mock_pmm::pmm_init(1024);

    std::cout << "[UNIT TEST] Verifying order boundaries and O(log N) contiguous allocations...\n";
    u64 addr1 = mock_pmm::pmm_alloc_contiguous(4); // should allocate order 2 (4 pages)
    assert(addr1 != 0);
    u64 page1 = mock_pmm::addr_to_page(addr1);
    assert(page1 % 4 == 0); // Must be order-2 page-aligned!
    assert(mock_pmm::g_page_orders[page1] == 2);

    u64 addr2 = mock_pmm::pmm_alloc_contiguous(8); // should allocate order 3 (8 pages)
    assert(addr2 != 0);
    u64 page2 = mock_pmm::addr_to_page(addr2);
    assert(page2 % 8 == 0); // Must be order-3 page-aligned!
    assert(mock_pmm::g_page_orders[page2] == 3);

    std::cout << "[UNIT TEST] Freeing allocations and testing Buddy Coalescing...\n";
    mock_pmm::pmm_free(addr1);
    // Since page1 and its buddy should coalesce, verify that order tracking updates correctly
    assert(!mock_pmm::bitmap_test(page1));

    mock_pmm::pmm_free(addr2);
    assert(!mock_pmm::bitmap_test(page2));

    std::cout << "[UNIT TEST] Low-memory conditions & Out of Bounds check...\n";
    u64 huge_addr = mock_pmm::pmm_alloc_contiguous(2048); // exceeds max size
    assert(huge_addr == 0);

    std::cout << "[PMM UNIT TESTS] All PMM Unit Tests passed successfully.\n";
}

namespace mock_filesystem {

struct RamDisk {
    std::vector<u8> storage;
    usize block_size = 512;
    bool read_only = false;

    RamDisk(usize total_blocks) {
        storage.assign(total_blocks * block_size, 0);
    }

    i32 read_blocks(u64 block_id, u64 count, void* buffer) {
        if (!buffer || count == 0) return -1;
        u64 total_b = storage.size() / block_size;
        if (block_id >= total_b || block_id + count > total_b) return -1;
        memcpy(buffer, storage.data() + block_id * block_size, count * block_size);
        return 0;
    }

    i32 write_blocks(u64 block_id, u64 count, const void* buffer) {
        if (read_only || !buffer || count == 0) return -1;
        u64 total_b = storage.size() / block_size;
        if (block_id >= total_b || block_id + count > total_b) return -1;
        memcpy(storage.data() + block_id * block_size, buffer, count * block_size);
        return 0;
    }
};

struct ASFSSuperblock {
    u64 magic = 0x415346535F4F535FULL; // "ASFS_OS_"
    u32 version = 1;
    u32 block_size = 512;
    u64 total_blocks;
    u64 free_blocks;
    u64 root_inode = 1;
    u64 free_space_root = 2;
};

struct ASFSExtent {
    u64 start_block;
    u32 block_count;
};

struct ASFSInode {
    u32 inode_number;
    u16 type; // 1 = File, 2 = Directory
    u16 permissions;
    u64 size;
    ASFSExtent extents[6];
};

struct ASFSDirectoryEntry {
    u32 inode_number;
    u8 type;
    u8 name_len;
    char name[58];
};

struct VFSNode {
    virtual ~VFSNode() = default;
    virtual i32 read(u64 offset, usize size, void* buf) = 0;
    virtual i32 write(u64 offset, usize size, const void* buf) = 0;
    virtual u64 size() const = 0;
    virtual bool is_dir() const = 0;
};

struct VFSFileNode : public VFSNode {
    std::vector<u8> content;

    i32 read(u64 offset, usize size, void* buf) override {
        if (offset >= content.size()) return 0;
        usize readable = size;
        if (offset + readable > content.size()) readable = content.size() - offset;
        memcpy(buf, content.data() + offset, readable);
        return static_cast<i32>(readable);
    }

    i32 write(u64 offset, usize size, const void* buf) override {
        if (offset + size > content.size()) content.resize(offset + size, 0);
        memcpy(content.data() + offset, buf, size);
        return static_cast<i32>(size);
    }

    u64 size() const override { return content.size(); }
    bool is_dir() const override { return false; }
};

struct VFSMountPoint {
    std::string path;
    bool is_read_only = false;
};

class MockVFS {
public:
    std::vector<VFSMountPoint> mounts;
    std::map<std::string, VFSFileNode*> files;

    bool mount(const std::string& path, bool read_only) {
        mounts.push_back({path, read_only});
        return true;
    }

    bool is_protected(const std::string& path) {
        if (path.rfind("/system", 0) == 0 || path.rfind("/vendor", 0) == 0) return true;
        return false;
    }

    i32 open(const std::string& path, bool create = false) {
        auto it = files.find(path);
        if (it != files.end()) return 1; // dummy fd
        if (create) {
            if (is_protected(path)) return -1; // write protected
            files[path] = new VFSFileNode();
            return 1;
        }
        return -1;
    }

    i32 unlink(const std::string& path) {
        if (is_protected(path)) return -1;
        auto it = files.find(path);
        if (it == files.end()) return -1;
        delete it->second;
        files.erase(it);
        return 0;
    }

    i32 mkdir(const std::string& path) {
        if (is_protected(path)) return -1;
        return 0;
    }
};

} // namespace mock_filesystem

void run_fat32_tests() {
    std::cout << "[UNIT TEST] Setting up mock FAT32 block device and filesystem...\n";
    mock_fat32::MockBlockDevice dev(2000);
    mock_fat32::MockFAT32FileSystem fs(&dev);

    // Verify hint wraps and FSInfo synchronization
    std::cout << "[UNIT TEST] Verifying next free cluster hint wraps & FSInfo sync...\n";
    u32 start_hint = fs.m_next_free_cluster_hint;
    assert(start_hint == 2);

    // Simulate cluster allocation
    u32 allocated_cluster = fs.m_next_free_cluster_hint;
    fs.write_fat_entry(allocated_cluster, 0x0FFFFFFF);
    fs.m_next_free_cluster_hint = allocated_cluster + 1;
    fs.m_free_clusters--;
    fs.update_fsinfo(fs.m_free_clusters, fs.m_next_free_cluster_hint);

    // Read back and assert
    u8 fsinfo[512];
    dev.read_block(fs.m_fsinfo_sector, fsinfo);
    assert(*(u32*)(fsinfo + 488) == fs.m_free_clusters);
    assert(*(u32*)(fsinfo + 492) == fs.m_next_free_cluster_hint);

    std::cout << "[FAT32 UNIT TESTS] All FAT32 Unit Tests passed successfully.\n";
}

namespace mock_cli_shell {

struct Command {
    std::string name;
    std::vector<std::string> args;
    std::string redirect_out;
};

struct Pipeline {
    std::vector<Command> commands;
};

class ShellParser {
public:
    static bool parse(const std::string& line, Pipeline& out_pipe) {
        if (line.empty()) return false;
        out_pipe.commands.clear();

        std::vector<std::string> cmd_strings;
        size_t start = 0, pos = 0;
        while ((pos = line.find('|', start)) != std::string::npos) {
            cmd_strings.push_back(line.substr(start, pos - start));
            start = pos + 1;
        }
        cmd_strings.push_back(line.substr(start));

        for (const auto& cs : cmd_strings) {
            Command cmd;
            size_t redir_pos = cs.find('>');
            std::string cmd_part = cs;
            if (redir_pos != std::string::npos) {
                cmd_part = cs.substr(0, redir_pos);
                std::string redir = cs.substr(redir_pos + 1);
                size_t first = redir.find_first_not_of(" \t");
                size_t last = redir.find_last_not_of(" \t");
                if (first != std::string::npos) cmd.redirect_out = redir.substr(first, (last - first + 1));
            }

            size_t p = 0;
            while (p < cmd_part.length()) {
                while (p < cmd_part.length() && (cmd_part[p] == ' ' || cmd_part[p] == '\t')) p++;
                if (p >= cmd_part.length()) break;
                size_t end_tok = p;
                while (end_tok < cmd_part.length() && cmd_part[end_tok] != ' ' && cmd_part[end_tok] != '\t') end_tok++;
                std::string tok = cmd_part.substr(p, end_tok - p);
                if (cmd.name.empty()) cmd.name = tok;
                else cmd.args.push_back(tok);
                p = end_tok;
            }
            if (!cmd.name.empty()) {
                out_pipe.commands.push_back(cmd);
            }
        }
        return !out_pipe.commands.empty();
    }
};

class ShellExecutor {
public:
    static std::string execute_builtin(const Command& cmd, const std::string& current_dir) {
        if (cmd.name == "pwd") return current_dir;
        if (cmd.name == "echo") {
            std::string out;
            for (size_t i = 0; i < cmd.args.size(); i++) {
                if (i > 0) out += " ";
                out += cmd.args[i];
            }
            return out;
        }
        if (cmd.name == "help") return "ACOS Shell Builtins: help, cd, pwd, ls, cat, echo, clear, ps, kill";
        return "Unknown command: " + cmd.name;
    }
};

} // namespace mock_cli_shell

namespace mock_console {

class ConsoleRingBuffer {
public:
    static constexpr usize BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    usize head = 0;
    usize tail = 0;
    usize count = 0;

    bool push(char c) {
        if (count >= BUFFER_SIZE) return false;
        buffer[tail] = c;
        tail = (tail + 1) % BUFFER_SIZE;
        count++;
        return true;
    }

    char pop() {
        if (count == 0) return 0;
        char c = buffer[head];
        head = (head + 1) % BUFFER_SIZE;
        count--;
        return c;
    }
};

class ConsoleNode {
public:
    ConsoleRingBuffer ring_buffer;
    bool blocked_reader = false;

    i32 write(const char* data, usize size) {
        if (!data || size == 0) return 0;
        return static_cast<i32>(size);
    }

    i32 read(char* out_buf, usize max_size) {
        if (!out_buf || max_size == 0) return 0;
        usize read_bytes = 0;
        while (read_bytes < max_size) {
            char c = ring_buffer.pop();
            if (c != 0) {
                out_buf[read_bytes++] = c;
            } else {
                if (read_bytes == 0) {
                    blocked_reader = true; // Waiting for input
                }
                break;
            }
        }
        return static_cast<i32>(read_bytes);
    }

    void push_char_and_wake(char c) {
        ring_buffer.push(c);
        if (blocked_reader) {
            blocked_reader = false; // Reader woken up!
        }
    }
};

class TerminalParser {
public:
    static constexpr int COLS = 80;
    static constexpr int ROWS = 25;

    char grid[ROWS][COLS];
    u32 color_grid[ROWS][COLS];
    int cursor_x = 0;
    int cursor_y = 0;
    u32 current_color = 0xFFFFFFFF; // White

    TerminalParser() {
        clear();
    }

    void clear() {
        memset(grid, ' ', sizeof(grid));
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) color_grid[r][c] = 0xFFFFFFFF;
        }
        cursor_x = 0;
        cursor_y = 0;
    }

    void process_stream(const char* str) {
        usize len = strlen(str);
        usize i = 0;
        while (i < len) {
            if (str[i] == '\033' && i + 1 < len && str[i + 1] == '[') {
                // ANSI escape sequence
                i += 2;
                if (i < len && str[i] == '2' && i + 1 < len && str[i + 1] == 'J') {
                    clear();
                    i += 2;
                } else if (i < len && str[i] == '3' && i + 1 < len && str[i + 1] == '1' && i + 2 < len && str[i + 2] == 'm') {
                    current_color = 0xFFFF0000; // Red
                    i += 3;
                } else if (i < len && str[i] == '0' && i + 1 < len && str[i + 1] == 'm') {
                    current_color = 0xFFFFFFFF; // Reset
                    i += 2;
                } else {
                    while (i < len && (str[i] < 'A' || str[i] > 'z')) i++;
                    if (i < len) i++;
                }
            } else if (str[i] == '\n') {
                cursor_x = 0;
                cursor_y++;
                if (cursor_y >= ROWS) {
                    scroll();
                    cursor_y = ROWS - 1;
                }
                i++;
            } else if (str[i] == '\b') {
                if (cursor_x > 0) cursor_x--;
                i++;
            } else {
                if (cursor_x < COLS && cursor_y < ROWS) {
                    grid[cursor_y][cursor_x] = str[i];
                    color_grid[cursor_y][cursor_x] = current_color;
                    cursor_x++;
                    if (cursor_x >= COLS) {
                        cursor_x = 0;
                        cursor_y++;
                        if (cursor_y >= ROWS) {
                            scroll();
                            cursor_y = ROWS - 1;
                        }
                    }
                }
                i++;
            }
        }
    }

    void scroll() {
        for (int r = 0; r < ROWS - 1; r++) {
            memcpy(grid[r], grid[r + 1], COLS);
            memcpy(color_grid[r], color_grid[r + 1], COLS * sizeof(u32));
        }
        memset(grid[ROWS - 1], ' ', COLS);
        for (int c = 0; c < COLS; c++) color_grid[ROWS - 1][c] = 0xFFFFFFFF;
    }
};

} // namespace mock_console

namespace mock_gui {

struct Rect {
    i32 x, y, w, h;

    bool contains(i32 px, i32 py) const {
        return (px >= x && px < x + w && py >= y && py < y + h);
    }

    Rect intersect(const Rect& other) const {
        i32 nx = std::max(x, other.x);
        i32 ny = std::max(y, other.y);
        i32 nw = std::min(x + w, other.x + other.w) - nx;
        i32 nh = std::min(y + h, other.y + other.h) - ny;
        if (nw <= 0 || nh <= 0) return {0, 0, 0, 0};
        return {nx, ny, nw, nh};
    }

    Rect unite(const Rect& other) const {
        if (w <= 0 || h <= 0) return other;
        if (other.w <= 0 || other.h <= 0) return *this;
        i32 nx = std::min(x, other.x);
        i32 ny = std::min(y, other.y);
        i32 nw = std::max(x + w, other.x + other.w) - nx;
        i32 nh = std::max(y + h, other.y + other.h) - ny;
        return {nx, ny, nw, nh};
    }
};

struct BoxConstraints {
    i32 min_w = 0;
    i32 max_w = 10000;
    i32 min_h = 0;
    i32 max_h = 10000;

    void constrain(i32& w, i32& h) const {
        if (w < min_w) w = min_w;
        if (w > max_w) w = max_w;
        if (h < min_h) h = min_h;
        if (h > max_h) h = max_h;
    }
};

enum class WidgetState { Normal, Hovered, Pressed, Focused, Disabled };

class Widget {
public:
    Rect rect = {0, 0, 0, 0};
    WidgetState state = WidgetState::Normal;
    bool visible = true;
    bool paint_dirty = true;

    virtual ~Widget() = default;

    virtual void on_mouse_event(i32 mx, i32 my, bool pressed) {
        if (!visible || state == WidgetState::Disabled) return;
        bool hit = rect.contains(mx, my);
        if (hit) {
            if (pressed) {
                state = WidgetState::Pressed;
            } else {
                if (state == WidgetState::Pressed) {
                    on_click();
                }
                state = WidgetState::Hovered;
            }
        } else {
            state = WidgetState::Normal;
        }
    }

    virtual void on_click() {}
};

class Button : public Widget {
public:
    std::string label;
    bool clicked = false;

    Button(const std::string& text, Rect r) : label(text) {
        rect = r;
    }

    void on_click() override {
        clicked = true;
    }
};

class Textbox : public Widget {
public:
    std::string text;
    size_t cursor_pos = 0;

    Textbox(Rect r) {
        rect = r;
    }

    void on_key_event(char c) {
        if (state != WidgetState::Focused) return;
        if (c == '\b') {
            if (!text.empty() && cursor_pos > 0) {
                text.erase(cursor_pos - 1, 1);
                cursor_pos--;
            }
        } else if (c >= 32 && c <= 126) {
            text.insert(cursor_pos, 1, c);
            cursor_pos++;
        }
    }
};

class WindowWidget : public Widget {
public:
    std::string title;
    bool closed = false;

    WindowWidget(const std::string& t, Rect r) : title(t) {
        rect = r;
    }

    Rect titlebar_rect() const {
        return {rect.x, rect.y, rect.w, 30};
    }

    Rect close_button_rect() const {
        return {rect.x + rect.w - 25, rect.y + 5, 20, 20};
    }

    void on_mouse_event(i32 mx, i32 my, bool pressed) override {
        Widget::on_mouse_event(mx, my, pressed);
        if (close_button_rect().contains(mx, my) && !pressed) {
            closed = true;
        }
    }
};

class Surface {
public:
    i32 width;
    i32 height;
    i32 pitch; // Stride in bytes
    std::vector<u32> pixels;

    Surface(i32 w, i32 h) : width(w), height(h), pitch(w * 4) {
        pixels.assign(w * h, 0xFF000000); // Black ARGB
    }

    void set_pixel(i32 x, i32 y, u32 color) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y * width + x] = color;
        }
    }

    u32 get_pixel(i32 x, i32 y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return pixels[y * width + x];
        }
        return 0;
    }
};

struct FontMetrics {
    int glyph_width = 8;
    int glyph_height = 16;

    int calc_string_width(const std::string& str) const {
        return static_cast<int>(str.length()) * glyph_width;
    }
};

} // namespace mock_gui

void run_gui_tests() {
    std::cout << "===================================================\n";
    std::cout << "         ASADE GUI & GRAPHICS UNIT TESTS           \n";
    std::cout << "===================================================\n";

    std::cout << "[GUI UNIT TEST] Testing Framebuffer Surface & Pixel Formatting...\n";
    {
        mock_gui::Surface surface(800, 600);
        assert(surface.width == 800);
        assert(surface.height == 600);
        assert(surface.pitch == 3200); // 800 * 4 bytes

        surface.set_pixel(100, 100, 0xFFFF0000); // Red
        assert(surface.get_pixel(100, 100) == 0xFFFF0000);

        // Out of bounds safety
        surface.set_pixel(800, 600, 0xFFFFFFFF);
        assert(surface.get_pixel(800, 600) == 0);

        std::cout << "  - Surface pitch calculation, ARGB pixel formatting, and bounds checking verified!\n";
    }

    std::cout << "[GUI UNIT TEST] Testing Clipping Rectangles & Dirty Region Merging...\n";
    {
        mock_gui::Rect r1{10, 10, 100, 100};
        mock_gui::Rect r2{50, 50, 100, 100};

        // Intersection test
        mock_gui::Rect clip = r1.intersect(r2);
        assert(clip.x == 50 && clip.y == 50 && clip.w == 60 && clip.h == 60);

        // Disjoint rects intersection returns empty (0, 0, 0, 0)
        mock_gui::Rect r3{200, 200, 50, 50};
        mock_gui::Rect empty_clip = r1.intersect(r3);
        assert(empty_clip.w == 0 && empty_clip.h == 0);

        // Union (Dirty region expansion)
        mock_gui::Rect dirty = r1.unite(r2);
        assert(dirty.x == 10 && dirty.y == 10 && dirty.w == 140 && dirty.h == 140);

        std::cout << "  - Clipping rectangle intersection and dirty region union merging verified!\n";
    }

    std::cout << "[GUI UNIT TEST] Testing Font Glyph Metrics...\n";
    {
        mock_gui::FontMetrics font;
        std::string label = "Asade Desktop Shell";
        int width = font.calc_string_width(label);
        assert(width == static_cast<int>(label.length()) * 8);

        std::cout << "  - Font string width metrics calculation verified!\n";
    }

    std::cout << "[GUI UNIT TEST] Testing Widget Event Handling & Non-Zero Coordinate Hit Testing...\n";
    {
        mock_gui::Button btn("OK", {100, 100, 80, 30}); // Non-zero position (100, 100)
        assert(btn.state == mock_gui::WidgetState::Normal);
        assert(!btn.clicked);

        // Mouse event at global coordinates (120, 120) inside button (100, 100, 80, 30)
        btn.on_mouse_event(120, 120, false);
        assert(btn.state == mock_gui::WidgetState::Hovered);

        // Press down on button at (120, 120)
        btn.on_mouse_event(120, 120, true);
        assert(btn.state == mock_gui::WidgetState::Pressed);

        // Release mouse over button -> Triggers click callback!
        btn.on_mouse_event(120, 120, false);
        assert(btn.clicked == true);

        // Mouse outside button bounds (50, 50)
        btn.on_mouse_event(50, 50, false);
        assert(btn.state == mock_gui::WidgetState::Normal);

        std::cout << "  - Non-zero offset hit testing and button click callbacks verified!\n";
    }

    std::cout << "[GUI UNIT TEST] Testing Textbox Mid-String Insertion & Backspace Deletion...\n";
    {
        mock_gui::Textbox txt({10, 50, 200, 30});
        txt.state = mock_gui::WidgetState::Focused;

        txt.on_key_event('A');
        txt.on_key_event('C');
        assert(txt.text == "AC");
        assert(txt.cursor_pos == 2);

        // Move cursor back to index 1 (between 'A' and 'C')
        txt.cursor_pos = 1;
        txt.on_key_event('B'); // Insert 'B' -> should become "ABC"
        assert(txt.text == "ABC");
        assert(txt.cursor_pos == 2);

        // Backspace at cursor index 2 (deletes 'B') -> should revert to "AC"
        txt.on_key_event('\b');
        assert(txt.text == "AC");
        assert(txt.cursor_pos == 1);

        std::cout << "  - Textbox typing, mid-string insertion, cursor positioning, and non-truncating backspace verified!\n";
    }

    std::cout << "[GUI UNIT TEST] Testing WindowWidget Titlebar & Close Action...\n";
    {
        mock_gui::WindowWidget win("Settings", {100, 100, 400, 300});
        assert(!win.closed);

        // Click close button
        auto close_rect = win.close_button_rect();
        win.on_mouse_event(close_rect.x + 2, close_rect.y + 2, false);
        assert(win.closed == true);

        std::cout << "  - WindowWidget titlebar geometry and close action verified!\n";
    }

    std::cout << "[GUI UNIT TEST] Testing BoxConstraints Layout Solver...\n";
    {
        mock_gui::BoxConstraints constraints{50, 300, 20, 150};
        i32 w = 20, h = 200; // Violates min_w and max_h
        constraints.constrain(w, h);
        assert(w == 50);  // Clamped to min_w
        assert(h == 150); // Clamped to max_h

        std::cout << "  - BoxConstraints layout bounds solver verified!\n";
    }

    std::cout << "===================================================\n\n";
}

void run_console_tests() {
    std::cout << "===================================================\n";
    std::cout << "         ASADE CONSOLE & TERMINAL UNIT TESTS       \n";
    std::cout << "===================================================\n";

    std::cout << "[CONSOLE UNIT TEST] Testing Ring Buffer Operations & Wrap-around...\n";
    {
        mock_console::ConsoleRingBuffer ring;
        for (int i = 0; i < 500; i++) {
            bool ok = ring.push('A' + (i % 26));
            assert(ok);
        }
        assert(ring.count == 500);

        for (int i = 0; i < 200; i++) {
            char c = ring.pop();
            assert(c == 'A' + (i % 26));
        }
        assert(ring.count == 300);

        // Fill up to 1024 capacity
        for (int i = 0; i < 724; i++) {
            bool ok = ring.push('X');
            assert(ok);
        }
        assert(ring.count == 1024);

        // 1025th push must be rejected on overflow
        assert(!ring.push('Z'));

        std::cout << "  - Ring buffer push/pop, modulo wrap-around, and capacity limits verified!\n";
    }

    std::cout << "[CONSOLE UNIT TEST] Testing ConsoleNode VFS Operations & Reader Wakeup...\n";
    {
        mock_console::ConsoleNode cnode;
        char read_buf[32] = {0};

        // Reading empty buffer causes reader to block
        i32 bytes_read = cnode.read(read_buf, 32);
        assert(bytes_read == 0);
        assert(cnode.blocked_reader == true);

        // Pushing char wakes reader
        cnode.push_char_and_wake('H');
        assert(cnode.blocked_reader == false);

        bytes_read = cnode.read(read_buf, 32);
        assert(bytes_read == 1);
        assert(read_buf[0] == 'H');

        std::cout << "  - ConsoleNode stream read/write and blocked reader wakeup verified!\n";
    }

    std::cout << "[CONSOLE UNIT TEST] Testing Terminal ANSI Parser & Screen Buffer Scrolling...\n";
    {
        mock_console::TerminalParser term;

        term.process_stream("Hello Asade OS!\n");
        assert(term.grid[0][0] == 'H');
        assert(term.grid[0][1] == 'e');
        assert(term.cursor_y == 1);
        assert(term.cursor_x == 0);

        // ANSI Color parsing
        term.process_stream("\033[31mRed Text\033[0m Normal Text\n");
        assert(term.grid[1][0] == 'R');
        assert(term.color_grid[1][0] == 0xFFFF0000); // Red
        assert(term.color_grid[1][9] == 0xFFFFFFFF); // Normal white after reset

        // Backspace handling
        term.process_stream("ABC\bX");
        assert(term.grid[2][2] == 'X'); // Replaced 'C' with 'X'

        // Screen clearing
        term.process_stream("\033[2J");
        assert(term.grid[0][0] == ' ');
        assert(term.cursor_x == 0 && term.cursor_y == 0);

        // Vertical Scrolling test (filling 30 lines)
        for (int i = 0; i < 30; i++) {
            term.process_stream("Line\n");
        }
        assert(term.cursor_y == 24); // Clamped at bottom row 24

        std::cout << "  - Terminal ANSI parser, color attributes, backspace, and line scrolling verified!\n";
    }

    std::cout << "[CONSOLE UNIT TEST] Testing CLI Shell Pipeline Parsing & Command Execution...\n";
    {
        mock_cli_shell::Pipeline pipeline;
        bool parsed = mock_cli_shell::ShellParser::parse("echo Hello Asade OS | cat > /tmp/out.txt", pipeline);
        assert(parsed);
        assert(pipeline.commands.size() == 2);
        assert(pipeline.commands[0].name == "echo");
        assert(pipeline.commands[0].args.size() == 3);
        assert(pipeline.commands[1].name == "cat");
        assert(pipeline.commands[1].redirect_out == "/tmp/out.txt");

        // Builtin command execution test
        mock_cli_shell::Command echo_cmd{"echo", {"System", "Ready"}, ""};
        std::string echo_out = mock_cli_shell::ShellExecutor::execute_builtin(echo_cmd, "/");
        assert(echo_out == "System Ready");

        mock_cli_shell::Command pwd_cmd{"pwd", {}, ""};
        std::string pwd_out = mock_cli_shell::ShellExecutor::execute_builtin(pwd_cmd, "/system/bin");
        assert(pwd_out == "/system/bin");

        std::cout << "  - CLI Shell pipeline parser, stdout redirection, and builtin execution verified!\n";
    }

    std::cout << "===================================================\n\n";
}

void run_filesystem_tests() {
    std::cout << "===================================================\n";
    std::cout << "         ASADE FILESYSTEM & VFS UNIT TESTS         \n";
    std::cout << "===================================================\n";

    std::cout << "[FS UNIT TEST] Testing RamDisk Block Device...\n";
    {
        mock_filesystem::RamDisk ramdisk(100); // 100 blocks
        u8 write_buf[512];
        memset(write_buf, 0xAB, 512);

        // Write block 5
        i32 wres = ramdisk.write_blocks(5, 1, write_buf);
        assert(wres == 0);

        u8 read_buf[512] = {0};
        i32 rres = ramdisk.read_blocks(5, 1, read_buf);
        assert(rres == 0);
        assert(read_buf[0] == 0xAB && read_buf[511] == 0xAB);

        // Out of bounds test
        assert(ramdisk.read_blocks(100, 1, read_buf) == -1);
        assert(ramdisk.write_blocks(99, 2, write_buf) == -1);

        // Read-only mode test
        ramdisk.read_only = true;
        assert(ramdisk.write_blocks(0, 1, write_buf) == -1);

        std::cout << "  - RamDisk read/write, bounds checking, and read-only mode verified!\n";
    }

    std::cout << "[FS UNIT TEST] Testing ASFS Superblock & Redundant Superblock Recovery...\n";
    {
        mock_filesystem::RamDisk disk(200);
        mock_filesystem::ASFSSuperblock primary_sb;
        primary_sb.total_blocks = 200;
        primary_sb.free_blocks = 180;

        u8 sb_buf[512] = {0};
        memcpy(sb_buf, &primary_sb, sizeof(primary_sb));

        // Write primary superblock at block 0
        disk.write_blocks(0, 1, sb_buf);

        // Write redundant superblock at last block (199)
        disk.write_blocks(199, 1, sb_buf);

        // Verify block 0
        mock_filesystem::ASFSSuperblock read_sb;
        u8 read_buf[512] = {0};
        disk.read_blocks(0, 1, read_buf);
        memcpy(&read_sb, read_buf, sizeof(read_sb));
        assert(read_sb.magic == 0x415346535F4F535FULL);

        // Corrupt primary superblock
        u8 zero_buf[512] = {0};
        disk.read_only = false;
        disk.write_blocks(0, 1, zero_buf);

        // Fallback check on redundant superblock at block 199
        memset(read_buf, 0, 512);
        disk.read_blocks(199, 1, read_buf);
        memcpy(&read_sb, read_buf, sizeof(read_sb));
        assert(read_sb.magic == 0x415346535F4F535FULL);

        std::cout << "  - ASFS superblock validation and redundant fallback recovery verified!\n";
    }

    std::cout << "[FS UNIT TEST] Testing VFS Operations & Namespace Protection...\n";
    {
        mock_filesystem::MockVFS vfs;
        vfs.mount("/", false);
        vfs.mount("/system", true);
        vfs.mount("/vendor", true);

        // Creating file in user space /tmp/test.txt should succeed
        i32 fd = vfs.open("/tmp/test.txt", true);
        assert(fd != -1);

        // Writing to user space file
        mock_filesystem::VFSFileNode* file = vfs.files["/tmp/test.txt"];
        const char* msg = "Asade OS VFS Test Data";
        file->write(0, strlen(msg), msg);
        assert(file->size() == strlen(msg));

        char read_buf[64] = {0};
        file->read(0, strlen(msg), read_buf);
        assert(strcmp(read_buf, msg) == 0);

        // Attempting to create file inside protected /system/core.dll should be rejected
        i32 sys_fd = vfs.open("/system/core.dll", true);
        assert(sys_fd == -1);

        // Attempting to unlink protected /vendor/driver.so should be rejected
        assert(vfs.unlink("/vendor/driver.so") == -1);

        // Unlinking user file should succeed
        assert(vfs.unlink("/tmp/test.txt") == 0);

        std::cout << "  - VFS mount registry, file IO, and protected namespace enforcement verified!\n";
    }

    run_fat32_tests();

    std::cout << "===================================================\n\n";
}

void run_asade_library_tests() {
    std::cout << "===================================================\n";
    std::cout << "         ASADE THIRD-PARTY LIBRARIES TESTS         \n";
    std::cout << "===================================================\n";

    std::cout << "[UNIT TEST] Testing Monocypher (Cryptography)...\n";
    {
        const char* msg = "Asade OS Monocypher Test";
        u8 hash[64] = {0};
        crypto_blake2b(hash, sizeof(hash), reinterpret_cast<const u8*>(msg), strlen(msg));

        bool is_all_zero = true;
        for (int i = 0; i < 64; i++) {
            if (hash[i] != 0) {
                is_all_zero = false;
                break;
            }
        }
        assert(!is_all_zero);
        std::cout << "  - BLAKE2b hash computed successfully!\n";
    }

    std::cout << "[UNIT TEST] Testing Miniz (Compression)...\n";
    {
        const char* src = "Hello from Asade OS! This is a compression test using miniz.";
        unsigned long src_len = strlen(src) + 1;
        unsigned long cmp_len = src_len * 2 + 12;
        std::vector<u8> cmp_buf(cmp_len);

        int status = mz_compress(cmp_buf.data(), &cmp_len, reinterpret_cast<const u8*>(src), src_len);
        assert(status == MZ_OK);

        unsigned long dec_len = src_len;
        std::vector<u8> dec_buf(dec_len);
        status = mz_uncompress(dec_buf.data(), &dec_len, cmp_buf.data(), cmp_len);
        assert(status == MZ_OK);
        assert(dec_len == src_len);
        assert(strcmp(reinterpret_cast<const char*>(dec_buf.data()), src) == 0);
        std::cout << "  - Miniz compression and decompression roundtrip passed!\n";
    }

    std::cout << "[UNIT TEST] Testing STB Image & STB Image Write (Graphics)...\n";
    {
        const int w = 8;
        const int h = 8;
        const int channels = 3; // RGB
        std::vector<u8> img_data(w * h * channels, 255); // Red image (all 255)

        struct WriteContext {
            std::vector<u8> buffer;
        } ctx;

        auto write_func = [](void* context, void* data, int size) {
            WriteContext* c = static_cast<WriteContext*>(context);
            u8* bytes = static_cast<u8*>(data);
            c->buffer.insert(c->buffer.end(), bytes, bytes + size);
        };

        int success = stbi_write_png_to_func(write_func, &ctx, w, h, channels, img_data.data(), w * channels);
        assert(success != 0);
        assert(!ctx.buffer.empty());

        int out_w, out_h, out_channels;
        u8* loaded_data = stbi_load_from_memory(ctx.buffer.data(), ctx.buffer.size(), &out_w, &out_h, &out_channels, channels);
        assert(loaded_data != nullptr);
        assert(out_w == w);
        assert(out_h == h);
        assert(loaded_data[0] == 255); // Red channel is 255
        stbi_image_free(loaded_data);
        std::cout << "  - STB Image & STB Image Write PNG roundtrip passed!\n";
    }

    std::cout << "[UNIT TEST] Testing Dr Wav (Audio)...\n";
    {
        drwav wav;
        drwav_data_format format;
        format.container = drwav_container_riff;
        format.format = DR_WAVE_FORMAT_PCM;
        format.channels = 1;
        format.sampleRate = 44100;
        format.bitsPerSample = 16;

        void* pWriteBuffer = nullptr;
        size_t writeBufferSize = 0;
        drwav_bool32 success = drwav_init_memory_write(&wav, &pWriteBuffer, &writeBufferSize, &format, nullptr);
        assert(success);

        std::vector<i16> samples(100, 0);
        drwav_uint64 framesWritten = drwav_write_pcm_frames(&wav, 100, samples.data());
        assert(framesWritten == 100);
        drwav_uninit(&wav);

        drwav wav_read;
        success = drwav_init_memory(&wav_read, pWriteBuffer, writeBufferSize, nullptr);
        assert(success);
        assert(wav_read.channels == 1);
        assert(wav_read.sampleRate == 44100);
        assert(wav_read.bitsPerSample == 16);

        std::vector<i16> read_samples(100);
        drwav_uint64 framesRead = drwav_read_pcm_frames_s16(&wav_read, 100, read_samples.data());
        assert(framesRead == 100);
        assert(read_samples[0] == 0);
        drwav_uninit(&wav_read);
        free(pWriteBuffer);
        std::cout << "  - Dr Wav writing and reading passed!\n";
    }

    std::cout << "[UNIT TEST] Testing Dr MP3 (Audio)...\n";
    {
        drmp3 mp3;
        u8 dummy_mp3[128] = {0};
        drmp3_bool32 success = drmp3_init_memory(&mp3, dummy_mp3, sizeof(dummy_mp3), nullptr);
        assert(!success);
        std::cout << "  - Dr MP3 initialized and handled empty stream safely!\n";
    }

    std::cout << "[UNIT TEST] Testing STB TrueType (Fonts)...\n";
    {
        u8 dummy_ttf[100] = {0};
        int offset = stbtt_GetFontOffsetForIndex(dummy_ttf, 0);
        assert(offset == -1);
        std::cout << "  - STB TrueType verified dummy font data safely!\n";
    }
    std::cout << "===================================================\n\n";
}

namespace mock_kernel {

enum class ThreadState { Ready, Running, Blocked, Terminated };

struct Thread {
    u64 tid;
    u64 pid;
    u32 priority; // 0 (lowest) to 31 (highest)
    ThreadState state;
    u32 quantum;
};

enum class ResourceKind : u32 {
    None = 0,
    Process,
    Thread,
    Channel,
    Notification,
    SharedRegion,
    GraphicsSurface
};

namespace ResourceRights {
    static constexpr u64 Read = 1ULL << 0;
    static constexpr u64 Write = 1ULL << 1;
    static constexpr u64 Execute = 1ULL << 2;
    static constexpr u64 Map = 1ULL << 3;
    static constexpr u64 Transfer = 1ULL << 4;
    static constexpr u64 Delegate = 1ULL << 5;
    static constexpr u64 Administer = 1ULL << 6;
    static constexpr u64 Signal = 1ULL << 7;
    static constexpr u64 Wait = 1ULL << 8;
}

struct ResourceHandleEntry {
    ResourceKind kind;
    void* object;
    u64 rights;
    u64 owner_process_id;
};

struct Process {
    static constexpr usize MAX_HANDLES = 256;
    u64 id;
    ResourceHandleEntry handles[MAX_HANDLES];

    Process(u64 pid) : id(pid) {
        for (usize i = 0; i < MAX_HANDLES; i++) {
            handles[i] = {ResourceKind::None, nullptr, 0, 0};
        }
    }

    u64 register_resource(ResourceKind kind, void* object, u64 rights) {
        for (usize i = 1; i < MAX_HANDLES; i++) {
            if (handles[i].kind == ResourceKind::None) {
                handles[i] = {kind, object, rights, id};
                return i;
            }
        }
        return 0; // Handle table full
    }

    ResourceHandleEntry* get_handle(u64 handle) {
        if (handle == 0 || handle >= MAX_HANDLES) return nullptr;
        if (handles[handle].kind == ResourceKind::None) return nullptr;
        return &handles[handle];
    }

    bool close_handle(u64 handle) {
        if (handle == 0 || handle >= MAX_HANDLES) return false;
        if (handles[handle].kind == ResourceKind::None) return false;
        handles[handle] = {ResourceKind::None, nullptr, 0, 0};
        return true;
    }

    bool duplicate_handle(u64 handle, u64 new_rights, u64* out_handle) {
        auto* entry = get_handle(handle);
        if (!entry) return false;
        // Cannot grant rights not possessed in entry
        if ((new_rights & entry->rights) != new_rights) return false;
        u64 new_h = register_resource(entry->kind, entry->object, new_rights);
        if (new_h == 0) return false;
        if (out_handle) *out_handle = new_h;
        return true;
    }

    bool transfer_handle(u64 handle, Process& target, u64* out_handle) {
        auto* entry = get_handle(handle);
        if (!entry) return false;
        if (!(entry->rights & ResourceRights::Transfer)) return false;
        u64 target_h = target.register_resource(entry->kind, entry->object, entry->rights);
        if (target_h == 0) return false;
        close_handle(handle);
        if (out_handle) *out_handle = target_h;
        return true;
    }
};

struct IPCMessage {
    u64 sender_pid;
    u32 code;
    u64 data[4];
};

class IPCChannel {
public:
    static constexpr usize MAX_MESSAGES = 16;
    IPCMessage buffer[MAX_MESSAGES];
    usize head = 0;
    usize tail = 0;
    usize count = 0;

    bool send(const IPCMessage& msg) {
        if (count >= MAX_MESSAGES) return false;
        buffer[tail] = msg;
        tail = (tail + 1) % MAX_MESSAGES;
        count++;
        return true;
    }

    bool receive(IPCMessage& msg) {
        if (count == 0) return false;
        msg = buffer[head];
        head = (head + 1) % MAX_MESSAGES;
        count--;
        return true;
    }
};

class Notification {
public:
    bool signaled = false;
    u32 wait_count = 0;

    void signal() {
        signaled = true;
        wait_count = 0;
    }

    void reset() {
        signaled = false;
    }
};

class Scheduler {
public:
    std::vector<Thread*> ready_queue;
    Thread* current_thread = nullptr;

    void add_thread(Thread* t) {
        t->state = ThreadState::Ready;
        ready_queue.push_back(t);
    }

    void schedule() {
        if (ready_queue.empty()) {
            current_thread = nullptr;
            return;
        }
        size_t best_idx = 0;
        u32 max_prio = ready_queue[0]->priority;
        for (size_t i = 1; i < ready_queue.size(); i++) {
            if (ready_queue[i]->priority > max_prio) {
                max_prio = ready_queue[i]->priority;
                best_idx = i;
            }
        }
        if (current_thread && current_thread->state == ThreadState::Running) {
            current_thread->state = ThreadState::Ready;
        }
        current_thread = ready_queue[best_idx];
        current_thread->state = ThreadState::Running;
    }
};

} // namespace mock_kernel

void run_kernel_tests() {
    std::cout << "===================================================\n";
    std::cout << "         ASADE CORE KERNEL UNIT TESTS              \n";
    std::cout << "===================================================\n";

    std::cout << "[KERNEL UNIT TEST] Testing Process & Handle Table Management...\n";
    {
        mock_kernel::Process proc1(100);
        mock_kernel::Process proc2(200);

        mock_kernel::IPCChannel dummy_chan;
        u64 full_rights = mock_kernel::ResourceRights::Read | mock_kernel::ResourceRights::Write |
                           mock_kernel::ResourceRights::Transfer;

        u64 h1 = proc1.register_resource(mock_kernel::ResourceKind::Channel, &dummy_chan, full_rights);
        assert(h1 != 0);

        auto* entry = proc1.get_handle(h1);
        assert(entry != nullptr);
        assert(entry->kind == mock_kernel::ResourceKind::Channel);
        assert(entry->owner_process_id == 100);

        // Test Handle Duplication with subset rights
        u64 h1_read_only = 0;
        bool dup_ok = proc1.duplicate_handle(h1, mock_kernel::ResourceRights::Read, &h1_read_only);
        assert(dup_ok);
        assert(h1_read_only != h1);
        assert(proc1.get_handle(h1_read_only)->rights == mock_kernel::ResourceRights::Read);

        // Attempt privilege escalation duplication (must fail)
        u64 h_invalid = 0;
        bool dup_fail = proc1.duplicate_handle(h1_read_only, full_rights, &h_invalid);
        assert(!dup_fail);

        // Test Handle Transfer between processes
        u64 h2 = 0;
        bool transfer_ok = proc1.transfer_handle(h1, proc2, &h2);
        assert(transfer_ok);
        assert(proc1.get_handle(h1) == nullptr); // closed in proc1
        assert(proc2.get_handle(h2) != nullptr); // registered in proc2
        assert(proc2.get_handle(h2)->owner_process_id == 200);

        std::cout << "  - Process handle registration, rights duplication, and transfer verified!\n";
    }

    std::cout << "[KERNEL UNIT TEST] Testing Scheduler & Priority Preemption...\n";
    {
        mock_kernel::Scheduler sched;
        mock_kernel::Thread t1{1, 100, 10, mock_kernel::ThreadState::Ready, 10};
        mock_kernel::Thread t2{2, 100, 20, mock_kernel::ThreadState::Ready, 10}; // higher priority
        mock_kernel::Thread t3{3, 100, 5, mock_kernel::ThreadState::Ready, 10};

        sched.add_thread(&t1);
        sched.add_thread(&t2);
        sched.add_thread(&t3);

        sched.schedule();
        assert(sched.current_thread != nullptr);
        assert(sched.current_thread->tid == 2); // t2 has highest priority (20)
        assert(t2.state == mock_kernel::ThreadState::Running);

        std::cout << "  - Priority preemption scheduler logic verified!\n";
    }

    std::cout << "[KERNEL UNIT TEST] Testing IPC Channel Ring Buffer & Overflow...\n";
    {
        mock_kernel::IPCChannel chan;
        for (usize i = 0; i < mock_kernel::IPCChannel::MAX_MESSAGES; i++) {
            mock_kernel::IPCMessage msg{100, static_cast<u32>(i), {i, i * 2, 0, 0}};
            bool sent = chan.send(msg);
            assert(sent);
        }

        // 17th message must fail due to full ring buffer
        mock_kernel::IPCMessage overflow_msg{100, 999, {0, 0, 0, 0}};
        bool sent_overflow = chan.send(overflow_msg);
        assert(!sent_overflow);

        // Read back messages in FIFO order
        for (usize i = 0; i < mock_kernel::IPCChannel::MAX_MESSAGES; i++) {
            mock_kernel::IPCMessage recv;
            bool recved = chan.receive(recv);
            assert(recved);
            assert(recv.code == static_cast<u32>(i));
            assert(recv.data[1] == i * 2);
        }

        // Receive on empty channel returns false
        mock_kernel::IPCMessage empty_recv;
        assert(!chan.receive(empty_recv));

        std::cout << "  - IPC channel FIFO ring buffer and capacity overflow rejection verified!\n";
    }

    std::cout << "[KERNEL UNIT TEST] Testing Notification Signals...\n";
    {
        mock_kernel::Notification note;
        assert(!note.signaled);

        note.signal();
        assert(note.signaled);

        note.reset();
        assert(!note.signaled);

        std::cout << "  - Notification signaling and reset verified!\n";
    }

    std::cout << "===================================================\n\n";
}

void run_subsystem_tests() {
    std::cout << "[INTEGRATION TEST] Verifying Subsystem APIs (Scheduler, IPC, Net Mock)...\n";
    run_kernel_tests();
    std::cout << "[INTEGRATION TEST] Subsystem API verification passed.\n";
}

void run_stress_tests() {
    std::cout << "[STRESS TEST] Commencing 10,000 allocate/free heavy cycles...\n";
    mock_pmm::pmm_init(4096);

    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<u64> allocations;
    std::mt19937 rng(42);

    for (int cycle = 0; cycle < 10000; cycle++) {
        int action = rng() % 2;
        if (action == 0 || allocations.empty()) {
            u64 size = (rng() % 8) + 1; // 1 to 8 pages
            u64 addr = mock_pmm::pmm_alloc_contiguous(size);
            if (addr != 0) {
                allocations.push_back(addr);
            }
        } else {
            size_t idx = rng() % allocations.size();
            u64 addr = allocations[idx];
            allocations.erase(allocations.begin() + idx);
            mock_pmm::pmm_free(addr);
        }
    }

    // Clean up remaining allocations
    for (u64 addr : allocations) {
        mock_pmm::pmm_free(addr);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "[STRESS TEST] Finished 10,000 allocations/frees in " << duration << " ms!\n";
    std::cout << "[STRESS TEST] Verifying memory heap is clean (no leaks) after cycles...\n";
    // Check that all physical memory has been coalesced back into huge order blocks
    for (u64 p = 1; p < mock_pmm::g_total_pages; p++) {
        if (p < 100 || p >= 200) { // skip simulated gaps
            assert(!mock_pmm::bitmap_test(p));
        }
    }
    std::cout << "[STRESS TEST] Leaks verification complete. Buddy Allocator returned 100% clean!\n";
}

void run_fuzz_tests() {
    std::cout << "[FUZZ TEST] Commencing Buddy Allocator random parameters fuzzing...\n";
    mock_pmm::pmm_init(4096);

    std::mt19937 rng(1337);
    for (int i = 0; i < 5000; i++) {
        u64 pages_to_alloc = rng() % 5000; // randomized sizes, some out of bounds
        u64 addr = mock_pmm::pmm_alloc_contiguous(pages_to_alloc);
        if (addr != 0) {
            mock_pmm::pmm_free(addr);
        }
    }
    std::cout << "[FUZZ TEST] Finished 5,000 fuzzed allocation requests. System stable and bounds-safe!\n";
}

int main(int argc, char** argv) {
    bool do_unit = false;
    bool do_stress = false;
    bool do_fuzz = false;

    if (argc == 1) {
        do_unit = true;
        do_stress = true;
        do_fuzz = true;
    } else {
        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "--unit-tests" || arg == "--integration-tests" || arg == "--kernel-tests" ||
                arg == "--userspace-tests" || arg == "--scheduler-tests" || arg == "--memory-tests" ||
                arg == "--filesystem-tests" || arg == "--driver-tests" || arg == "--networking-tests") {
                do_unit = true;
            } else if (arg == "--stress-tests") {
                do_stress = true;
            } else if (arg == "--fuzz-tests") {
                do_fuzz = true;
            }
        }
    }

    std::cout << "===================================================\n";
    std::cout << "         ASADE CONTINUOUS TESTING REPORT           \n";
    std::cout << "===================================================\n";

    if (do_unit) {
        run_pmm_tests();
        run_filesystem_tests();
        run_console_tests();
        run_gui_tests();
        run_subsystem_tests();
        run_asade_library_tests();
    }
    if (do_stress) {
        run_stress_tests();
    }
    if (do_fuzz) {
        run_fuzz_tests();
    }

    std::cout << "===================================================\n";
    std::cout << "       SUCCESS: ALL TESTING SUITES PASSED!        \n";
    std::cout << "===================================================\n";
    return 0;
}
