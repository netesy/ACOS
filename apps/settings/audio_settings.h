#pragma once
#include <userland/gui/widget.h>
#include <userland/gui/label.h>
#include <userland/gui/listview.h>

namespace acos::apps {

class AudioSettings : public gui::Widget {
public:
    AudioSettings();
    void draw(acos::graphics::Renderer* renderer) override;

private:
    gui::Label m_title;
    gui::ListView m_device_list;
};

} // namespace acos::apps
