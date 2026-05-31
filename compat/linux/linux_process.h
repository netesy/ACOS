#pragma once
#include <acos/types.h>
#include <kernel/scheduler/process.h>

namespace acos::compat::linux {

class LinuxProcess {
public:
    LinuxProcess(scheduler::Process* acos_proc);

    u64 linux_pid() const { return m_acos_proc->id; }
    scheduler::Process* acos_process() const { return m_acos_proc; }

private:
    scheduler::Process* m_acos_proc;
};

} // namespace acos::compat::linux
