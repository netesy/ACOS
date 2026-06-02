#include "menu.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Menu::Menu() {
    m_rect.w = 150;
    m_rect.h = 200;
}

Menu::~Menu() {}

void Menu::add_item(const char* label) {
    m_list.add_item(label);
}

void Menu::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    renderer->draw_shadow(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 4, 100);
    m_list.set_position(m_rect.x, m_rect.y);
    m_list.set_size(m_rect.w, m_rect.h);
    m_list.draw(renderer);
}

void Menu::handle_event(const acos::input::InputEvent& event) {
    m_list.handle_event(event);
}

} // namespace acos::gui
