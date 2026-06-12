#include <acos/process.h>
#include <acos/runtime.h>
#include "settings.h"
#include <userland/gui/text.h>
#include <userland/gui/button.h>
#include <userland/gui/checkbox.h>
#include <userland/gui/slider.h>
#include <userland/gui/switch.h>
#include <userland/gui/core/context.h>
#include <userland/gui/core/flex.h>

namespace acos::apps {

Settings::Settings() : gui::WindowWidget("Settings", 100, 100, 400, 400) {
    auto& region = gui::UIContext::get().region();
    auto root = region.alloc<gui::widgets::Column>();
    root->set_rect({10, 40, 380, 350});
    root->padding(10);
    
    auto title = region.alloc<gui::widgets::Text>("System Customization");
    title->font_size(18);
    root->add_child(title.static_cast_to<gui::Widget>());
    
    auto dark_mode = region.alloc<gui::widgets::Switch>("Dark Mode");
    dark_mode->set_on(true);
    root->add_child(dark_mode.static_cast_to<gui::Widget>());
    
    auto transparency = region.alloc<gui::widgets::CheckBox>("Enable Transparency");
    transparency->set_checked(true);
    root->add_child(transparency.static_cast_to<gui::Widget>());

    auto volume_label = region.alloc<gui::widgets::Text>("System Volume");
    root->add_child(volume_label.static_cast_to<gui::Widget>());

    auto volume_slider = region.alloc<gui::widgets::Slider>();
    volume_slider->set_value(70.0f);
    root->add_child(volume_slider.static_cast_to<gui::Widget>());

    auto btn_row = region.alloc<gui::widgets::Row>();
    btn_row->set_rect({0, 0, 360, 40});

    auto apply_btn = region.alloc<gui::widgets::Button>("Apply");
    auto reset_btn = region.alloc<gui::widgets::Button>("Reset");

    btn_row->add_child(apply_btn.static_cast_to<gui::Widget>());
    btn_row->add_child(reset_btn.static_cast_to<gui::Widget>());

    root->add_child(btn_row.static_cast_to<gui::Widget>());

    add_child(root.static_cast_to<gui::Widget>());
}

} // namespace acos::apps
