#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/vfs.h>
#include <acos/syscall.h>
#include "launcher.h"
#include <acos/renderer.h>
#include <userland/gui/theme.h>
#include <userland/gui/text.h>
#include <userland/gui/icon.h>
#include <userland/gui/panel.h>
#include <userland/gui/core/flex.h>
#include <userland/gui/core/context.h>

namespace acos::shell {

class LauncherIcon : public gui::widgets::Icon {
public:
    LauncherIcon(gui::widgets::IconType type, const char* path)
        : gui::widgets::Icon(type) {
        usize len = 0;
        while (path[len] && len < 127) {
            m_path[len] = path[len];
            len++;
        }
        m_path[len] = '\0';
    }

    void on_event(gui::Event& event) override {
        const auto& raw = event.raw;
        if (raw.type == ::acos::abi::InputType::Mouse) {
            ::acos::i32 mx = event.mouse_x;
            ::acos::i32 my = event.mouse_y;
            bool pressed = (raw.value & 0x01) != 0;

            if (m_rect.contains(mx, my)) {
                if (!pressed && m_state == gui::WidgetState::Pressed) {
                    // Launch the application via Capability ProcessCreate APIs!
                    u64 proc = syscall(sys::SyscallNum::ProcessCreate, reinterpret_cast<u64>(m_path), 0, 0, 0, 0);
                    if (proc != 0 && proc != static_cast<u64>(-1)) {
                        syscall(sys::SyscallNum::ProcessStart, proc, 0, 0, 0, 0);
                    }
                }
                m_state = pressed ? gui::WidgetState::Pressed : gui::WidgetState::Hovered;
            } else {
                m_state = gui::WidgetState::Normal;
            }
            set_paint_dirty();
        }
    }

private:
    char m_path[128];
};

Launcher::Launcher() {
    m_rect = {10, 60, 240, 360};
    m_active = false;
    set_glass(true);
    set_visible(false);

    auto& region = gui::UIContext::get().region();

    auto col_layout = region.alloc<gui::widgets::Column>();
    col_layout->spacing(12);

    auto title = region.alloc<gui::widgets::Text>("Applications Launcher");
    title->color(0xFFFFFFFF);
    col_layout->add_child(title.static_cast_to<gui::Widget>());

    // Enumerate applications dynamically from /bin using VFS API
    static vfs::DirectoryEntry entries[16];
    i32 n = vfs::read_dir("/bin", entries, 16);
    if (n >= 0) {
        for (i32 i = 0; i < n; i++) {
            if (entries[i].type == vfs::NodeType::File) {
                auto item = region.alloc<gui::widgets::Row>();
                item->spacing(8);

                char full_path[128];
                ::memcpy(full_path, "/bin/", 5);
                usize len = 0;
                while (entries[i].name[len] && len < 120) {
                    full_path[5 + len] = entries[i].name[len];
                    len++;
                }
                full_path[5 + len] = '\0';

                auto icon = region.alloc<LauncherIcon>(gui::widgets::IconType::Code, full_path);
                icon->set_rect({0, 0, 24, 24});
                item->add_child(icon.static_cast_to<gui::Widget>());

                // Format name
                char label[64];
                usize label_len = 0;
                while (entries[i].name[label_len] && label_len < 63) {
                    label[label_len] = entries[i].name[label_len];
                    label_len++;
                }
                label[label_len] = '\0';
                if (label[0] >= 'a' && label[0] <= 'z') label[0] -= 32;

                // Strip .elf suffix for visual elegance
                if (label_len > 4 && label[label_len - 4] == '.') {
                    label[label_len - 4] = '\0';
                }

                auto text = region.alloc<gui::widgets::Text>(label);
                text->color(0xFFCCCCCC);
                item->add_child(text.static_cast_to<gui::Widget>());

                col_layout->add_child(item.static_cast_to<gui::Widget>());
            }
        }
    }

    add_child(col_layout.static_cast_to<gui::Widget>());
}

void Launcher::show() { set_visible(true); m_active = true; }
void Launcher::hide() { set_visible(false); m_active = false; }

gui::Ref<gui::RenderObject> Launcher::create_render_object() {
    return gui::widgets::Panel::create_render_object();
}

void Launcher::update_render_object(gui::Ref<gui::RenderObject> render_object) {
    gui::widgets::Panel::update_render_object(render_object);
}

} // namespace acos::shell
