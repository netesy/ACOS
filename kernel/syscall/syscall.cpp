#include <kernel/syscall/syscall.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/scheduler/process.h>
#include <kernel/ipc/channel.h>
#include <kernel/ipc/notification.h>
#include <kernel/vfs/file.h>
#include <kernel/vfs/vfs.h>
#include <kernel/memory/heap.h>
#include <kernel/loader/process_loader.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::syscall {

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

extern "C" u64 syscall_dispatch(u64 num, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5) {
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
            scheduler::Process* target = current->get_process(arg1);
            if (!target || !target->primary_thread) return kErrInvalid;

            scheduler::wake_thread(target->primary_thread);
            return 0;
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

        case SyscallNum::ThreadJoin: {
            scheduler::Thread* thread = current ? current->get_thread(arg1) : nullptr;
            if (!thread) return kErrInvalid;
            while (thread->state != scheduler::ThreadState::Terminated) {
                scheduler::schedule();
            }
            return 0;
        }

        case SyscallNum::ThreadTerminate: {
            scheduler::Thread* thread = current ? current->get_thread(arg1) : nullptr;
            if (!thread || !has_rights(current, arg1, scheduler::ResourceRights::Administer)) return kErrAccess;
            thread->state = scheduler::ThreadState::Terminated;
            return 0;
        }

        case SyscallNum::ResourceClose:
        case SyscallNum::ResourceRevoke:
            return (current && current->close_handle(arg1)) ? 0 : kErrInvalid;

        case SyscallNum::ResourceQuery: {
            if (!current || !arg2) return kErrInvalid;
            scheduler::ResourceHandleEntry* entry = current->get_handle(arg1);
            if (!entry) return kErrInvalid;
            ResourceInfo* info = reinterpret_cast<ResourceInfo*>(arg2);
            info->type = static_cast<u64>(entry->kind);
            info->id = arg1;
            info->rights = entry->rights;
            info->owner = entry->owner_process_id;
            info->state = 0;
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
            return static_cast<u64>(vfs::VFS::read(fd, buffer, size));
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

        default:
            return static_cast<u64>(-1);
    }
}

} // namespace acos::syscall
