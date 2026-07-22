#include <kernel/syscall/syscall.h>
#include <kernel/hal/serial.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/scheduler/process.h>
#include <kernel/services/service_registry.h>
#include <kernel/graphics/surface.h>
#include <kernel/graphics/graphics_manager.h>
#include <kernel/graphics/context.h>
#include <kernel/graphics/clipping.h>
#include <kernel/graphics/dirty_region.h>
#include <kernel/ipc/channel.h>
#include <kernel/ipc/notification.h>
#include <kernel/vfs/file.h>
#include <kernel/vfs/vfs.h>
#include <kernel/memory/heap.h>
#include <kernel/loader/process_loader.h>
#include <libs/runtime/include/acos/runtime.h>
#include <kernel/input/input_manager.h>
#include <kernel/input/input_queue.h>
#include <kernel/input/input_device.h>

namespace acos::sys {

namespace {

constexpr u64 kErrInvalid = static_cast<u64>(-1);
constexpr u64 kErrAccess = static_cast<u64>(-2);
constexpr u64 kErrNoMemory = static_cast<u64>(-3);

bool has_rights(acos::scheduler::Process* process, u64 handle, u64 rights) {
    if (!process) {
        return false;
    }
    acos::scheduler::ResourceHandleEntry* entry = process->get_handle(handle);
    return entry && ((entry->rights & rights) == rights);
}

} // namespace

class PipeNode final {
public:
    PipeNode() : m_reader_refs(0), m_writer_refs(0), m_head(0), m_tail(0), m_count(0), m_closed(false) {
        m_buffer = static_cast<char*>(memory::kmalloc(65536)); // 64KB buffer
        if (m_buffer) {
            memset(m_buffer, 0, 65536);
        }
        for (usize i = 0; i < ipc::Channel::MAX_WAITERS; i++) {
            m_readers[i] = nullptr;
            m_writers[i] = nullptr;
        }
        m_reader_count = 0;
        m_writer_count = 0;
    }

    ~PipeNode() {
        if (m_buffer) {
            memory::kfree(m_buffer);
        }
    }

    void add_ref(bool is_writer) {
        hal::ScopedLock lock(m_lock);
        if (is_writer) m_writer_refs++;
        else m_reader_refs++;
    }

    void dec_ref(bool is_writer) {
        hal::ScopedLock lock(m_lock);
        if (is_writer) {
            if (m_writer_refs > 0) m_writer_refs--;
        } else {
            if (m_reader_refs > 0) m_reader_refs--;
        }
        if (m_writer_refs == 0 && m_reader_refs == 0) {
            close_internal();
        }
    }

    i32 read(usize size, void* buffer) {
        hal::ScopedLock lock(m_lock);
        char* out = static_cast<char*>(buffer);
        usize copied = 0;

        while (copied < size) {
            if (m_count > 0) {
                out[copied++] = m_buffer[m_head];
                m_head = (m_head + 1) % 65536;
                m_count--;

                // Wake one waiting writer
                if (m_writer_count > 0) {
                    scheduler::wake_thread(m_writers[0]);
                    for (usize i = 0; i < m_writer_count - 1; i++) m_writers[i] = m_writers[i+1];
                    m_writer_count--;
                }
            } else {
                if (m_closed || m_writer_refs == 0 || copied > 0) {
                    break;
                }
                // Block reader
                auto* current = scheduler::current_thread();
                if (m_reader_count < ipc::Channel::MAX_WAITERS) {
                    m_readers[m_reader_count++] = current;
                    m_lock.unlock();
                    scheduler::block_thread(current);
                    m_lock.lock();
                } else {
                    break;
                }
            }
        }
        return static_cast<i32>(copied);
    }

    i32 write(usize size, const void* buffer) {
        hal::ScopedLock lock(m_lock);
        const char* in = static_cast<const char*>(buffer);
        usize copied = 0;

        while (copied < size) {
            if (m_closed || m_reader_refs == 0) return -1;
            if (m_count < 65536) {
                m_buffer[m_tail] = in[copied++];
                m_tail = (m_tail + 1) % 65536;
                m_count++;

                // Wake one waiting reader
                if (m_reader_count > 0) {
                    scheduler::wake_thread(m_readers[0]);
                    for (usize i = 0; i < m_reader_count - 1; i++) m_readers[i] = m_readers[i+1];
                    m_reader_count--;
                }
            } else {
                // Block writer
                auto* current = scheduler::current_thread();
                if (m_writer_count < ipc::Channel::MAX_WAITERS) {
                    m_writers[m_writer_count++] = current;
                    m_lock.unlock();
                    scheduler::block_thread(current);
                    m_lock.lock();
                } else {
                    break;
                }
            }
        }
        return static_cast<i32>(copied);
    }

    u64 size() const { return m_count; }

    void close_internal() {
        m_closed = true;
        for (usize i = 0; i < m_reader_count; i++) {
            scheduler::wake_thread(m_readers[i]);
        }
        m_reader_count = 0;
        for (usize i = 0; i < m_writer_count; i++) {
            scheduler::wake_thread(m_writers[i]);
        }
        m_writer_count = 0;
    }

    u32 m_reader_refs;
    u32 m_writer_refs;

private:
    hal::SpinLock m_lock;
    char* m_buffer;
    usize m_head;
    usize m_tail;
    usize m_count;
    bool m_closed;

    scheduler::Thread* m_readers[ipc::Channel::MAX_WAITERS];
    usize m_reader_count;
    scheduler::Thread* m_writers[ipc::Channel::MAX_WAITERS];
    usize m_writer_count;
};

class PipeFileNode final : public vfs::Node {
public:
    PipeFileNode(PipeNode* shared, bool is_writer) : m_shared(shared), m_is_writer(is_writer), m_node_refs(1) {
        m_shared->add_ref(m_is_writer);
    }

    ~PipeFileNode() override {}

    void add_ref() override {
        m_node_refs++;
    }

    void close_node() override {
        m_node_refs--;
        if (m_node_refs == 0) {
            m_shared->dec_ref(m_is_writer);
            if (m_shared->m_writer_refs == 0 && m_shared->m_reader_refs == 0) {
                m_shared->~PipeNode();
                memory::kfree(m_shared);
            }
            this->~PipeFileNode();
            memory::kfree(this);
        }
    }

    i32 read(u64 offset [[maybe_unused]], usize size, void* buffer) override {
        if (m_is_writer) return -1;
        return m_shared->read(size, buffer);
    }

    i32 write(u64 offset [[maybe_unused]], usize size, const void* buffer) override {
        if (!m_is_writer) return -1;
        return m_shared->write(size, buffer);
    }

    u64 size() const override { return m_shared->size(); }
    vfs::NodeType type() const override { return vfs::NodeType::File; }

private:
    PipeNode* m_shared;
    bool m_is_writer;
    u32 m_node_refs;
};

extern "C" u64 syscall_dispatch(u64 num, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5) {
    acos::hal::serial_print("[SYSCALL] num=");
    acos::hal::serial_print_hex(num);
    acos::hal::serial_print(" arg1=");
    acos::hal::serial_print_hex(arg1);
    acos::hal::serial_print(" arg2=");
    acos::hal::serial_print_hex(arg2);
    acos::hal::serial_print(" arg3=");
    acos::hal::serial_print_hex(arg3);
    acos::hal::serial_print("\n");
    (void)arg4; (void)arg5;
    auto* current_thr = scheduler::current_thread();
    if (!current_thr && static_cast<SyscallNum>(num) != SyscallNum::Yield) {
        return static_cast<u64>(-1);
    }

    auto* current = current_thr ? current_thr->parent : nullptr;

    switch (static_cast<SyscallNum>(num)) {
        case SyscallNum::Exit:
            if (current_thr) {
                current_thr->state = scheduler::ThreadState::Terminated;
                scheduler::schedule();
            }
            return 0;

        case SyscallNum::Yield:
            scheduler::schedule();
            return 0;

        case SyscallNum::GetPid:
            return current ? current->id : 0;

        case SyscallNum::ProcessCreate: {
            if (!current) return kErrInvalid;
            const char* path = reinterpret_cast<const char*>(arg1);
            if (!path) return kErrInvalid;

            // Load ELF from VFS
            i32 fd = vfs::VFS::open(path, 0);
            if (fd < 0) return kErrInvalid;

            vfs::File* file = current->get_file(fd);
            if (!file) {
                vfs::VFS::close(fd);
                return kErrInvalid;
            }

            usize size = file->size();
            void* elf_data = memory::kmalloc(size);
            if (!elf_data) {
                vfs::VFS::close(fd);
                return kErrNoMemory;
            }

            file->read(elf_data, size);
            vfs::VFS::close(fd);

            scheduler::Process* child = loader::create_process_from_elf(path, elf_data, size);
            memory::kfree(elf_data);

            if (!child) return kErrNoMemory;

            // Handle Inheritance (FD 0, 1, 2)
            for (int i = 0; i < 3; i++) {
                if (current->files[i]) {
                    child->files[i] = current->files[i];
                }
            }

            return current->register_process(child, scheduler::ResourceRights::Administer | scheduler::ResourceRights::Transfer | scheduler::ResourceRights::Delegate);
        }

        case SyscallNum::ProcessStart: {
            if (!current) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(arg1);
            if (!entry) return kErrInvalid;
            if (entry->kind == scheduler::ResourceKind::Process) {
                scheduler::Process* target = static_cast<scheduler::Process*>(entry->object);
                if (target && target->primary_thread) {
                    scheduler::wake_thread(target->primary_thread);
                    return 0;
                }
            } else if (entry->kind == scheduler::ResourceKind::Thread) {
                scheduler::Thread* target = static_cast<scheduler::Thread*>(entry->object);
                if (target) {
                    scheduler::wake_thread(target);
                    return 0;
                }
            }
            return kErrInvalid;
        }

        case SyscallNum::ProcessTerminate: {
            if (!current || !has_rights(current, arg1, scheduler::ResourceRights::Administer)) return kErrAccess;
            scheduler::Process* process = current->get_process(arg1);
            if (!process) return kErrInvalid;
            (void)process;
            return 0;
        }

        case SyscallNum::ThreadCreate: {
            if (!current) return kErrInvalid;
            scheduler::Process* target = arg1 ? current->get_process(arg1) : current;
            if (!target) return kErrInvalid;
            scheduler::Thread* thread = scheduler::create_thread(reinterpret_cast<scheduler::ThreadEntry>(arg2), reinterpret_cast<void*>(arg3));
            if (!thread) return kErrNoMemory;
            thread->parent = target;
            return current->register_thread(thread, scheduler::ResourceRights::Administer | scheduler::ResourceRights::Transfer | scheduler::ResourceRights::Delegate);
        }

        case SyscallNum::ThreadSleep: {
            u64 ms = arg1;
            if (ms > 0) {
                scheduler::register_sleep(current_thr, ms);
                scheduler::block_thread(current_thr);
            } else {
                scheduler::schedule();
            }
            return 0;
        }

        case SyscallNum::ThreadJoin: {
            if (!current) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(arg1);
            if (!entry) return kErrInvalid;
            if (entry->kind == scheduler::ResourceKind::Thread) {
                scheduler::Thread* thread = static_cast<scheduler::Thread*>(entry->object);
                while (thread->state != scheduler::ThreadState::Terminated) {
                    scheduler::schedule();
                }
                return 0;
            } else if (entry->kind == scheduler::ResourceKind::Process) {
                scheduler::Process* proc = static_cast<scheduler::Process*>(entry->object);
                if (proc && proc->primary_thread) {
                    while (proc->primary_thread->state != scheduler::ThreadState::Terminated) {
                        scheduler::schedule();
                    }
                }
                return 0;
            }
            return kErrInvalid;
        }

        case SyscallNum::ThreadTerminate: {
            scheduler::Thread* thread = current ? current->get_thread(arg1) : nullptr;
            if (!thread || !has_rights(current, arg1, scheduler::ResourceRights::Administer)) return kErrAccess;
            thread->state = scheduler::ThreadState::Terminated;
            return 0;
        }

        case SyscallNum::ResourceClose:
        case SyscallNum::ResourceRevoke: {
            if (current) {
                scheduler::ResourceHandleEntry* entry = current->get_handle(arg1);
                if (entry && entry->kind == scheduler::ResourceKind::InputQueue) {
                    auto* queue = static_cast<input::InputQueue*>(entry->object);
                    if (queue) {
                        input::InputManager::unregister_queue(queue);
                        queue->~InputQueue();
                        memory::kfree(queue);
                    }
                }
                return current->close_handle(arg1) ? 0 : kErrInvalid;
            }
            return kErrInvalid;
        }

        case SyscallNum::ResourceQuery: {
            if (!current || !arg2) return kErrInvalid;
            if (arg1 == 0) {
                // Special case: handle 0 queries framebuffer info if called by DS
                auto* display = graphics::GraphicsManager::primary_display();
                if (display && display->get_framebuffer()) {
                    auto* fb = display->get_framebuffer();
                    struct FBInfo { u64 base, size; u32 w, h, p, bpp; };
                    FBInfo* info = reinterpret_cast<FBInfo*>(arg2);
                    info->base = 0xC000000000;
                    info->size = fb->size();
                    info->w = fb->width();
                    info->h = fb->height();
                    info->p = fb->pitch();
                    info->bpp = 32; // Assuming 32bpp
                    return 0;
                }
            }
            scheduler::ResourceHandleEntry* entry = current->get_handle(arg1);
            if (!entry) return kErrInvalid;
            ResourceInfo* info = reinterpret_cast<ResourceInfo*>(arg2);
            info->type = static_cast<u64>(entry->kind);
            info->id = arg1;
            info->rights = entry->rights;
            info->owner = entry->owner_process_id;
            info->state = 0;

            if (entry->kind == scheduler::ResourceKind::Process) {
                scheduler::Process* proc = static_cast<scheduler::Process*>(entry->object);
                if (proc && proc->primary_thread) {
                    info->state = (proc->primary_thread->state == scheduler::ThreadState::Terminated) ? 3 : 0;
                }
            } else if (entry->kind == scheduler::ResourceKind::Thread) {
                scheduler::Thread* thread = static_cast<scheduler::Thread*>(entry->object);
                if (thread) {
                    info->state = (thread->state == scheduler::ThreadState::Terminated) ? 3 : 0;
                }
            }
            return 0;
        }

        case SyscallNum::ResourceDuplicate: {
            if (!current || !arg3) return kErrInvalid;
            u64 duplicate = 0;
            if (!current->duplicate_handle(arg1, arg2, &duplicate)) return kErrAccess;
            *reinterpret_cast<u64*>(arg3) = duplicate;
            return 0;
        }

        case SyscallNum::ResourceTransfer: {
            if (!current || !arg3) return kErrInvalid;
            scheduler::Process* target = scheduler::find_process(arg2);
            if (!target) return kErrInvalid;
            u64 transferred = 0;
            if (!current->transfer_handle(arg1, *target, &transferred)) return kErrAccess;
            *reinterpret_cast<u64*>(arg3) = transferred;
            return 0;
        }

        case SyscallNum::ChannelCreate: {
            if (!current) return kErrInvalid;
            void* storage = memory::kmalloc(sizeof(ipc::Channel));
            if (!storage) return kErrNoMemory;
            ipc::Channel* channel = new (storage) ipc::Channel();
            const u64 handle = current->register_channel(channel);
            return handle ? handle : kErrNoMemory;
        }

        case SyscallNum::NotificationCreate: {
            if (!current) return kErrInvalid;
            void* storage = memory::kmalloc(sizeof(ipc::Notification));
            if (!storage) return kErrNoMemory;
            ipc::Notification* notification = new (storage) ipc::Notification();
            const u64 handle = current->register_notification(notification);
            return handle ? handle : kErrNoMemory;
        }

        // IPC: Channel Operations
        case SyscallNum::ChannelSend: {
            u64 handle = arg1;
            const ipc::Message* msg_ptr = reinterpret_cast<const ipc::Message*>(arg2);
            if (!current || !msg_ptr) return kErrInvalid;
            if (!has_rights(current, handle, scheduler::ResourceRights::Write)) return kErrAccess;
            auto* chan = current->get_channel(handle);
            if (!chan) return kErrInvalid;
            return static_cast<u64>(chan->send(*msg_ptr));
        }

        case SyscallNum::ChannelReceive: {
            u64 handle = arg1;
            ipc::Message* msg_ptr = reinterpret_cast<ipc::Message*>(arg2);
            if (!current || !msg_ptr) return kErrInvalid;
            if (!has_rights(current, handle, scheduler::ResourceRights::Read)) return kErrAccess;
            auto* chan = current->get_channel(handle);
            if (!chan) return kErrInvalid;
            return static_cast<u64>(chan->receive(*msg_ptr));
        }

        // IPC: Notification Operations
        case SyscallNum::NotificationSignal: {
            u64 handle = arg1;
            if (!current) return kErrInvalid;
            if (!has_rights(current, handle, scheduler::ResourceRights::Signal)) return kErrAccess;
            auto* note = current->get_notification(handle);
            if (!note) return kErrInvalid;
            note->signal();
            return 0;
        }

        case SyscallNum::NotificationWait: {
            u64 handle = arg1;
            if (!current) return kErrInvalid;
            if (!has_rights(current, handle, scheduler::ResourceRights::Wait)) return kErrAccess;
            auto* note = current->get_notification(handle);
            if (!note) return kErrInvalid;
            note->wait();
            return 0;
        }

        // VFS Operations
        case SyscallNum::FileOpen: {
            const char* path = reinterpret_cast<const char*>(arg1);
            u64 flags = arg2;
            if (!current) return static_cast<u64>(-1);
            return static_cast<u64>(vfs::VFS::open(path, flags));
        }

        case SyscallNum::FileClose: {
            u64 fd = arg1;
            if (!current) return static_cast<u64>(-1);
            return static_cast<u64>(vfs::VFS::close(fd));
        }

        case SyscallNum::FileRead: {
            u64 fd = arg1;
            void* buffer = reinterpret_cast<void*>(arg2);
            usize size = arg3;
            if (!current) return static_cast<u64>(-1);
            u64 res = static_cast<u64>(vfs::VFS::read(fd, buffer, size));
            if (res > 0 && res < 100) {
                acos::hal::serial_print("[Syscall] read returned ");
                acos::hal::serial_print_hex(res);
                acos::hal::serial_print(" byte(s)\n");
            }
            return res;
        }

        case SyscallNum::FileWrite: {
            u64 fd = arg1;
            const void* data = reinterpret_cast<const void*>(arg2);
            usize size = arg3;
            if (!current) return static_cast<u64>(-1);
            return static_cast<u64>(vfs::VFS::write(fd, data, size));
        }

        case SyscallNum::FileReadDir: {
            const char* path = reinterpret_cast<const char*>(arg1);
            vfs::DirectoryEntry* entries = reinterpret_cast<vfs::DirectoryEntry*>(arg2);
            usize max_entries = arg3;
            if (!current) return static_cast<u64>(-1);
            return static_cast<u64>(vfs::VFS::read_dir(path, entries, max_entries));
        }

        case SyscallNum::FileDup: {
            if (!current) return kErrInvalid;
            return static_cast<u64>(vfs::VFS::dup2(arg1, arg2));
        }

        case SyscallNum::PipeCreate: {
            if (!current) return kErrInvalid;
            i32* fds = reinterpret_cast<i32*>(arg1);
            if (!fds) return kErrInvalid;

            void* storage = memory::kmalloc(sizeof(PipeNode));
            if (!storage) return kErrNoMemory;
            PipeNode* pipe_shared = new (storage) PipeNode();

            void* rd_storage = memory::kmalloc(sizeof(PipeFileNode));
            if (!rd_storage) {
                pipe_shared->~PipeNode();
                memory::kfree(pipe_shared);
                return kErrNoMemory;
            }
            PipeFileNode* rd_node = new (rd_storage) PipeFileNode(pipe_shared, false);

            void* wr_storage = memory::kmalloc(sizeof(PipeFileNode));
            if (!wr_storage) {
                rd_node->~PipeFileNode();
                memory::kfree(rd_node);
                pipe_shared->~PipeNode();
                memory::kfree(pipe_shared);
                return kErrNoMemory;
            }
            PipeFileNode* wr_node = new (wr_storage) PipeFileNode(pipe_shared, true);

            void* rd_file_storage = memory::kmalloc(sizeof(vfs::File));
            if (!rd_file_storage) {
                wr_node->~PipeFileNode();
                memory::kfree(wr_node);
                rd_node->~PipeFileNode();
                memory::kfree(rd_node);
                pipe_shared->~PipeNode();
                memory::kfree(pipe_shared);
                return kErrNoMemory;
            }
            vfs::File* rd_file = new (rd_file_storage) vfs::File(rd_node);

            void* wr_file_storage = memory::kmalloc(sizeof(vfs::File));
            if (!wr_file_storage) {
                memory::kfree(rd_file_storage);
                wr_node->~PipeFileNode();
                memory::kfree(wr_node);
                rd_node->~PipeFileNode();
                memory::kfree(rd_node);
                pipe_shared->~PipeNode();
                memory::kfree(pipe_shared);
                return kErrNoMemory;
            }
            vfs::File* wr_file = new (wr_file_storage) vfs::File(wr_node);

            i32 rd_fd = current->register_file(rd_file);
            if (rd_fd < 0) {
                memory::kfree(wr_file_storage);
                memory::kfree(rd_file_storage);
                wr_node->~PipeFileNode();
                memory::kfree(wr_node);
                rd_node->~PipeFileNode();
                memory::kfree(rd_node);
                pipe_shared->~PipeNode();
                memory::kfree(pipe_shared);
                return kErrNoMemory;
            }

            i32 wr_fd = current->register_file(wr_file);
            if (wr_fd < 0) {
                current->files[rd_fd] = nullptr;
                memory::kfree(wr_file_storage);
                memory::kfree(rd_file_storage);
                wr_node->~PipeFileNode();
                memory::kfree(wr_node);
                rd_node->~PipeFileNode();
                memory::kfree(rd_node);
                pipe_shared->~PipeNode();
                memory::kfree(pipe_shared);
                return kErrNoMemory;
            }

            fds[0] = rd_fd;
            fds[1] = wr_fd;
            return 0;
        }

        case SyscallNum::ResourceLocate: {
            const char* name = reinterpret_cast<const char*>(arg1);
            if (!current || !name) return 0;
            ipc::Channel* channel = services::locate_service(name);
            if (!channel) return 0;

            return current->register_channel(channel);
        }

        case SyscallNum::ResourceRegister: {
            const char* name = reinterpret_cast<const char*>(arg1);
            u64 handle = arg2;
            if (!current || !name) return kErrInvalid;
            ipc::Channel* channel = current->get_channel(handle);
            if (!channel) return kErrInvalid;

            if (services::register_service(name, channel, current->id)) {
                return 0;
            }
            return kErrInvalid;
        }

        case SyscallNum::GraphicsSurfaceCreate: {
            u32 width = static_cast<u32>(arg1);
            u32 height = static_cast<u32>(arg2);
            if (!current || width == 0 || height == 0) return 0;
            void* storage = memory::kmalloc(sizeof(graphics::Surface));
            if (!storage) return kErrNoMemory;
            auto* surface = new (storage) graphics::Surface(width, height, true);
            return current->register_resource(scheduler::ResourceKind::GraphicsSurface, surface, scheduler::ResourceRights::Read | scheduler::ResourceRights::Write | scheduler::ResourceRights::Transfer);
        }

        case SyscallNum::GraphicsWindowCreate: {
            if (!current) return 0;
            // For now, Windows are user-space constructs. We track them for capability management.
            return current->register_resource(scheduler::ResourceKind::GraphicsWindow, nullptr, scheduler::ResourceRights::Read | scheduler::ResourceRights::Write);
        }

        case SyscallNum::GraphicsPresent: {
            u64 handle = arg1;
            if (!current) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(handle);
            if (!entry) return kErrInvalid;
            if (entry->kind == scheduler::ResourceKind::GraphicsSurface) {
                auto* surface = static_cast<graphics::Surface*>(entry->object);
                if (surface) {
                    surface->swap_buffers();
                    return 0;
                }
            }
            return kErrInvalid;
        }

        case SyscallNum::GraphicsGetFramebuffer: {
            if (!current) return 0;
            auto* display = graphics::GraphicsManager::primary_display();
            if (!display) return 0;
            auto* fb = display->get_framebuffer();
            if (!fb) return 0;

            // Exclusive access check: Only the Display Server should have access.
            // For now, we allow the first process that asks for it to be the "Display Server".
            // In a more mature system, we'd check a "DisplayServer" capability.
            static u64 display_server_pid = 0;
            if (display_server_pid == 0) {
                display_server_pid = current->id;
            } else if (display_server_pid != current->id) {
                return 0; // Permission Denied
            }
            
            // Map the physical framebuffer into the process's address space.
            // Fixed virtual address for the framebuffer in the service's address space.
            u64 fb_virt = 0xC000000000; 
            u64 fb_phys = fb->base();
            u64 fb_size = fb->size();

            for (u64 offset = 0; offset < fb_size; offset += 4096) {
                current->address_space->map(fb_virt + offset, fb_phys + offset, 
                    memory::PageFlags::Present | memory::PageFlags::Writable | memory::PageFlags::User | memory::PageFlags::NoCache);
            }

            return fb_virt;
        }

        case SyscallNum::GraphicsDisplayCreate: {
            if (!current) return 0;
            auto* display = graphics::GraphicsManager::primary_display();
            if (!display) return 0;
            return current->register_resource(scheduler::ResourceKind::GraphicsDisplay, display, scheduler::ResourceRights::Read | scheduler::ResourceRights::Write);
        }

        case SyscallNum::GraphicsBufferCreate: {
            u32 size = static_cast<u32>(arg1);
            if (!current || size == 0) return 0;
            void* buffer = memory::kmalloc(size);
            if (!buffer) return kErrNoMemory;
            return current->register_resource(scheduler::ResourceKind::GraphicsBuffer, buffer, scheduler::ResourceRights::Read | scheduler::ResourceRights::Write);
        }

        case SyscallNum::GraphicsResourceDestroy: {
            u64 handle = arg1;
            if (!current) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(handle);
            if (!entry) return kErrInvalid;

            if (entry->kind == scheduler::ResourceKind::GraphicsSurface) {
                auto* surface = static_cast<graphics::Surface*>(entry->object);
                if (surface) {
                    surface->~Surface();
                    memory::kfree(surface);
                }
            } else if (entry->kind == scheduler::ResourceKind::GraphicsContext) {
                auto* ctx = static_cast<graphics::GraphicsContext*>(entry->object);
                if (ctx) {
                    ctx->~GraphicsContext();
                    memory::kfree(ctx);
                }
            } else if (entry->kind == scheduler::ResourceKind::GraphicsBuffer) {
                if (entry->object) {
                    memory::kfree(entry->object);
                }
            }

            return current->close_handle(handle) ? 0 : kErrInvalid;
        }

        case SyscallNum::GraphicsResourceResize: {
            u64 handle = arg1;
            u32 width = static_cast<u32>(arg2);
            u32 height = static_cast<u32>(arg3);
            if (!current || width == 0 || height == 0) return kErrInvalid;

            scheduler::ResourceHandleEntry* entry = current->get_handle(handle);
            if (!entry || (entry->rights & scheduler::ResourceRights::Write) == 0) return kErrAccess;

            if (entry->kind == scheduler::ResourceKind::GraphicsSurface) {
                auto* surface = static_cast<graphics::Surface*>(entry->object);
                if (surface) {
                    surface->resize(width, height);
                    return 0;
                }
            }
            return kErrInvalid;
        }

        case SyscallNum::GraphicsContextCreate: {
            u64 target_handle = arg1;
            u32 target_type = static_cast<u32>(arg2); // 0 for Display, 1 for Surface
            if (!current) return 0;

            scheduler::ResourceHandleEntry* entry = current->get_handle(target_handle);
            if (!entry || (entry->rights & scheduler::ResourceRights::Write) == 0) return kErrAccess;

            graphics::GraphicsContext::TargetType t_type;

            if (target_type == 0 && entry->kind == scheduler::ResourceKind::GraphicsDisplay) {
                t_type = graphics::GraphicsContext::TargetType::Display;
            } else if (target_type == 1 && entry->kind == scheduler::ResourceKind::GraphicsSurface) {
                t_type = graphics::GraphicsContext::TargetType::Surface;
            } else {
                return kErrInvalid;
            }

            void* storage = memory::kmalloc(sizeof(graphics::GraphicsContext));
            if (!storage) return kErrNoMemory;

            auto* ctx = new (storage) graphics::GraphicsContext(t_type, target_handle);
            return current->register_resource(scheduler::ResourceKind::GraphicsContext, ctx, scheduler::ResourceRights::Read | scheduler::ResourceRights::Write);
        }

        case SyscallNum::GraphicsPutPixel: {
            u64 ctx_handle = arg1;
            u32 x = static_cast<u32>(arg2);
            u32 y = static_cast<u32>(arg3);
            u32 color = static_cast<u32>(arg4);

            if (!current) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(ctx_handle);
            if (!entry || entry->kind != scheduler::ResourceKind::GraphicsContext || (entry->rights & scheduler::ResourceRights::Write) == 0) return kErrAccess;

            auto* ctx = static_cast<graphics::GraphicsContext*>(entry->object);
            if (ctx) ctx->put_pixel(x, y, color);
            return 0;
        }

        case SyscallNum::GraphicsDrawLine: {
            u64 ctx_handle = arg1;
            u32 x1 = static_cast<u32>(arg2 >> 32);
            u32 y1 = static_cast<u32>(arg2 & 0xFFFFFFFF);
            u32 x2 = static_cast<u32>(arg3 >> 32);
            u32 y2 = static_cast<u32>(arg3 & 0xFFFFFFFF);
            u32 color = static_cast<u32>(arg4);

            if (!current) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(ctx_handle);
            if (!entry || entry->kind != scheduler::ResourceKind::GraphicsContext || (entry->rights & scheduler::ResourceRights::Write) == 0) return kErrAccess;

            auto* ctx = static_cast<graphics::GraphicsContext*>(entry->object);
            if (ctx) ctx->draw_line(x1, y1, x2, y2, color);
            return 0;
        }

        case SyscallNum::GraphicsDrawRect: {
            u64 ctx_handle = arg1;
            u32 x = static_cast<u32>(arg2 >> 32);
            u32 y = static_cast<u32>(arg2 & 0xFFFFFFFF);
            u32 w = static_cast<u32>(arg3 >> 32);
            u32 h = static_cast<u32>(arg3 & 0xFFFFFFFF);
            u32 color = static_cast<u32>(arg4);

            if (!current) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(ctx_handle);
            if (!entry || entry->kind != scheduler::ResourceKind::GraphicsContext || (entry->rights & scheduler::ResourceRights::Write) == 0) return kErrAccess;

            auto* ctx = static_cast<graphics::GraphicsContext*>(entry->object);
            if (ctx) ctx->draw_rect(x, y, w, h, color);
            return 0;
        }

        case SyscallNum::GraphicsFillRect: {
            u64 ctx_handle = arg1;
            u32 x = static_cast<u32>(arg2 >> 32);
            u32 y = static_cast<u32>(arg2 & 0xFFFFFFFF);
            u32 w = static_cast<u32>(arg3 >> 32);
            u32 h = static_cast<u32>(arg3 & 0xFFFFFFFF);
            u32 color = static_cast<u32>(arg4);

            if (!current) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(ctx_handle);
            if (!entry || entry->kind != scheduler::ResourceKind::GraphicsContext || (entry->rights & scheduler::ResourceRights::Write) == 0) return kErrAccess;

            auto* ctx = static_cast<graphics::GraphicsContext*>(entry->object);
            if (ctx) ctx->fill_rect(x, y, w, h, color);
            return 0;
        }

        case SyscallNum::GraphicsDrawCircle: {
            u64 ctx_handle = arg1;
            u32 cx = static_cast<u32>(arg2 >> 32);
            u32 cy = static_cast<u32>(arg2 & 0xFFFFFFFF);
            u32 radius = static_cast<u32>(arg3);
            u32 color = static_cast<u32>(arg4);

            if (!current) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(ctx_handle);
            if (!entry || entry->kind != scheduler::ResourceKind::GraphicsContext || (entry->rights & scheduler::ResourceRights::Write) == 0) return kErrAccess;

            auto* ctx = static_cast<graphics::GraphicsContext*>(entry->object);
            if (ctx) ctx->draw_circle(cx, cy, radius, color);
            return 0;
        }

        case SyscallNum::GraphicsFillCircle: {
            u64 ctx_handle = arg1;
            u32 cx = static_cast<u32>(arg2 >> 32);
            u32 cy = static_cast<u32>(arg2 & 0xFFFFFFFF);
            u32 radius = static_cast<u32>(arg3);
            u32 color = static_cast<u32>(arg4);

            if (!current) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(ctx_handle);
            if (!entry || entry->kind != scheduler::ResourceKind::GraphicsContext || (entry->rights & scheduler::ResourceRights::Write) == 0) return kErrAccess;

            auto* ctx = static_cast<graphics::GraphicsContext*>(entry->object);
            if (ctx) ctx->fill_circle(cx, cy, radius, color);
            return 0;
        }

        case SyscallNum::GraphicsBlit: {
            u64 ctx_handle = arg1;
            u32 dx = static_cast<u32>(arg2 >> 32);
            u32 dy = static_cast<u32>(arg2 & 0xFFFFFFFF);
            u64 src_surface_handle = arg3;
            u32 sx = static_cast<u32>(arg4 >> 32);
            u32 sy = static_cast<u32>(arg4 & 0xFFFFFFFF);
            u32 sw = static_cast<u32>(arg5 >> 32);
            u32 sh = static_cast<u32>(arg5 & 0xFFFFFFFF);

            if (!current) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(ctx_handle);
            if (!entry || entry->kind != scheduler::ResourceKind::GraphicsContext || (entry->rights & scheduler::ResourceRights::Write) == 0) return kErrAccess;

            scheduler::ResourceHandleEntry* src_entry = current->get_handle(src_surface_handle);
            if (!src_entry || src_entry->kind != scheduler::ResourceKind::GraphicsSurface) return kErrInvalid;

            auto* ctx = static_cast<graphics::GraphicsContext*>(entry->object);
            auto* src_surf = static_cast<graphics::Surface*>(src_entry->object);

            if (ctx && src_surf) {
                ctx->blit(dx, dy, src_surf, sx, sy, sw, sh);
            }
            return 0;
        }

        case SyscallNum::GraphicsClear: {
            u64 ctx_handle = arg1;
            u32 color = static_cast<u32>(arg2);

            if (!current) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(ctx_handle);
            if (!entry || entry->kind != scheduler::ResourceKind::GraphicsContext || (entry->rights & scheduler::ResourceRights::Write) == 0) return kErrAccess;

            auto* ctx = static_cast<graphics::GraphicsContext*>(entry->object);
            if (ctx) ctx->clear(color);
            return 0;
        }

        case SyscallNum::GraphicsCopyRect: {
            u64 ctx_handle = arg1;
            u32 dx = static_cast<u32>(arg2 >> 32);
            u32 dy = static_cast<u32>(arg2 & 0xFFFFFFFF);
            u32 sx = static_cast<u32>(arg3 >> 32);
            u32 sy = static_cast<u32>(arg3 & 0xFFFFFFFF);
            u32 w = static_cast<u32>(arg4 >> 32);
            u32 h = static_cast<u32>(arg4 & 0xFFFFFFFF);

            if (!current) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(ctx_handle);
            if (!entry || entry->kind != scheduler::ResourceKind::GraphicsContext || (entry->rights & scheduler::ResourceRights::Write) == 0) return kErrAccess;

            auto* ctx = static_cast<graphics::GraphicsContext*>(entry->object);
            if (ctx) ctx->copy_rect(dx, dy, sx, sy, w, h);
            return 0;
        }

        case SyscallNum::InputQueueCreate: {
            if (!current) return kErrInvalid;
            void* storage = memory::kmalloc(sizeof(input::InputQueue));
            if (!storage) return kErrNoMemory;
            auto* queue = new (storage) input::InputQueue();
            input::InputManager::register_queue(queue, current->id);
            return current->register_resource(scheduler::ResourceKind::InputQueue, queue, scheduler::ResourceRights::Read | scheduler::ResourceRights::Write | scheduler::ResourceRights::Transfer | scheduler::ResourceRights::Delegate);
        }

        case SyscallNum::InputQueuePop: {
            // Secure userspace pointer boundaries validation (prevents Write-What-Where exploits)
            if (!current || !arg2 || arg2 >= 0x800000000000ULL) return kErrInvalid;

            scheduler::ResourceHandleEntry* entry = current->get_handle(arg1);
            if (!entry || entry->kind != scheduler::ResourceKind::InputQueue || (entry->rights & scheduler::ResourceRights::Read) == 0) return kErrAccess;

            auto* queue = static_cast<input::InputQueue*>(entry->object);
            input::InputEvent ev;
            bool block = (arg3 != 0);
            if (queue->pop_event(ev, block)) {
                *reinterpret_cast<input::InputEvent*>(arg2) = ev;
                return 1;
            }
            return 0;
        }

        case SyscallNum::InputDeviceOpen: {
            if (!current) return kErrInvalid;
            auto* dev = input::InputManager::get_device_by_type(static_cast<input::InputType>(arg1));
            if (!dev) return kErrInvalid;
            return current->register_resource(scheduler::ResourceKind::InputDevice, dev, scheduler::ResourceRights::Read | scheduler::ResourceRights::Transfer);
        }

        default:
            return static_cast<u64>(-1);
    }
}

} // namespace acos::sys
