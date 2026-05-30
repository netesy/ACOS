#pragma once
#include <acos/types.h>
#include <kernel/scheduler/process.h>

namespace acos::loader {

scheduler::Process* create_process_from_elf(const char* name, const void* elf_data, usize size);

} // namespace acos::loader
