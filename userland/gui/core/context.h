#pragma once
#include "region.h"

namespace acos::gui {

class UIContext {
public:
    UIContext();
    ~UIContext();

    static UIContext& get();

    Region& region() { return m_main_region; }

private:
    Region m_main_region;
    static UIContext* s_instance;
};

} // namespace acos::gui
