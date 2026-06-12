#include <acos/process.h>
#include <acos/runtime.h>
#include "ref.h"
#include "region.h"

namespace acos::gui {

void* RefBaseResolve(Region* region, u32 index, u32 generation) {
    if (!region) return nullptr;
    return region->get_raw(index, generation);
}

} // namespace acos::gui
