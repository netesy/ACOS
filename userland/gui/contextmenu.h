#pragma once
#include "menu.h"

namespace acos::gui::widgets {

class ContextMenu : public Menu {
public:
    ContextMenu();
    virtual ~ContextMenu();
    void popup(::acos::i32 x, ::acos::i32 y);

    Ref<RenderObject> create_render_object() override;
};

} // namespace acos::gui::widgets
