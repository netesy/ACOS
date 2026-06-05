#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class Toast : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    Toast(const char* message);
    void update(u64 delta_ms) override;

    void show(u32 duration_ms = 3000);

private:
    const char* m_message;
    u32 m_timer;
    u32 m_duration;
    u8 m_alpha;
};

} // namespace acos::gui::widgets
