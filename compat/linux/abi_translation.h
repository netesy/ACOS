#pragma once
#include <acos/types.h>

namespace acos::compat::linux {

struct LinuxStat {
    u64 st_dev;
    u64 st_ino;
    u64 st_nlink;
    u32 st_mode;
    u32 st_uid;
    u32 st_gid;
    u32 pad0;
    u64 st_rdev;
    i64 st_size;
    i64 st_blksize;
    i64 st_blocks;
    u64 st_atime;
    u64 st_atime_nsec;
    u64 st_mtime;
    u64 st_mtime_nsec;
    u64 st_ctime;
    u64 st_ctime_nsec;
    i64 unused[3];
};

} // namespace acos::compat::linux
