#pragma once
#include <acos/types.h>

#define PER_CPU(type, name)     namespace percpu {         extern type name;     }

namespace acos::smp {
    void percpu_init();
}
