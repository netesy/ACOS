#pragma once
#include <userland/gui/widget.h>

namespace acos::shell {

class VolumeIndicator : public gui::Widget {
public:
    VolumeIndicator();
    void draw(u32* buffer, u32 pitch) override;
    void set_volume(u32 vol) { m_volume = vol; }

private:
    u32 m_volume;
};

} // namespace acos::shell
