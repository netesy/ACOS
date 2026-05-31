#pragma once
#include "widget.h"

namespace acos::gui {

class Label : public Widget {
public:
    Label(const char* text);
    void draw(u32* buffer, u32 pitch) override;

private:
    const char* m_text;
};

} // namespace acos::gui
