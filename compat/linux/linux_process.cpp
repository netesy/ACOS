#include "linux_process.h"

namespace acos::compat::linux {

LinuxProcess::LinuxProcess(scheduler::Process* acos_proc) : m_acos_proc(acos_proc) {}

} // namespace acos::compat::linux
