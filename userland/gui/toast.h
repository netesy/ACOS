#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class Toast : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    Toast(const char* message);
    virtual ~Toast();
    void update(::acos::u64 delta_ms) override;

    void show(::acos::u32 duration_ms = 3000);

private:
    [[maybe_unused]] const char* m_message;
    [[maybe_unused]] ::acos::u32 m_timer;
    [[maybe_unused]] ::acos::u32 m_duration;
    [[maybe_unused]] ::acos::u8 m_alpha;
};

} // namespace acos::gui::widgets
