#include "taskbar.h"
#include <userland/gui/theme.h>
#include <userland/gui/icon.h>

namespace acos::shell {

Taskbar::Taskbar() {
    m_rect = {0, 0, 800, 48};
    m_volume.set_position(750, 10);
    m_clock_str[0] = '\0';
}

void Taskbar::draw(acos::graphics::Renderer* renderer) {
    if (!renderer) return;

    renderer->blend_rect(static_cast<u32>(m_rect.x),
                        static_cast<u32>(m_rect.y),
                        static_cast<u32>(m_rect.w),
                        static_cast<u32>(m_rect.h),
                        gui::g_current_theme.glass_bg, 220);

    renderer->draw_line(static_cast<u32>(m_rect.x),
                        static_cast<u32>(m_rect.y),
                        static_cast<u32>(m_rect.x + m_rect.w - 1),
                        static_cast<u32>(m_rect.y),
                        gui::g_current_theme.border);

    gui::Icon terminal_icon(gui::IconType::Terminal);
    terminal_icon.set_position(20, 8);
    terminal_icon.draw(renderer);

    gui::Icon files_icon(gui::IconType::Files);
    files_icon.set_position(68, 8);
    files_icon.draw(renderer);

    gui::Icon code_icon(gui::IconType::Code);
    code_icon.set_position(116, 8);
    code_icon.set_active(true);
    code_icon.draw(renderer);

    gui::Icon settings_icon(gui::IconType::Settings);
    settings_icon.set_position(164, 8);
    settings_icon.draw(renderer);

    const char* clock_txt = m_clock_str[0] ? m_clock_str : "12:00 PM";
    renderer->draw_text(clock_txt, 700, 16, gui::g_current_theme.text,
                       acos::graphics::Font::Alignment::Left, acos::graphics::Font::Style::Regular);

    m_volume.draw(renderer);
}

void Taskbar::update_clock() {
    m_clock_str[0] = '1';
    m_clock_str[1] = '2';
    m_clock_str[2] = ':';
    m_clock_str[3] = '0';
    m_clock_str[4] = '0';
    m_clock_str[5] = ' ';
    m_clock_str[6] = 'P';
    m_clock_str[7] = 'M';
    m_clock_str[8] = '\0';
}

} // namespace acos::shell
