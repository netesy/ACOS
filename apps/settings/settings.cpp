#include "settings.h"
#include <userland/gui/theme.h>
#include <userland/gui/label.h>
#include <userland/gui/button.h>
#include <userland/gui/progressbar.h>
#include <userland/gui/checkbox.h>
#include <userland/gui/slider.h>
#include <userland/gui/layout.h>
#include <userland/gui/tabwidget.h>
#include <userland/gui/panel.h>
#include <userland/gui/switch.h>
#include <userland/gui/combobox.h>
#include <userland/gui/textarea.h>

namespace acos::apps {

Settings::Settings()
    : gui::WindowWidget("System Settings", 50, 50, 550, 450),
      m_display_btn("Apply"), m_theme_btn("Cancel") {
    
    auto tabs = new gui::TabWidget();
    tabs->set_position(10, 10);
    tabs->set_size(530, 330);
    add_child(tabs);

    // Activity Tab
    auto general_panel = new gui::Panel();
    tabs->add_tab("Activity", general_panel);
    
    auto cpu_label = new gui::Label("Kernel Activity");
    cpu_label->set_position(10, 10);
    general_panel->add_child(cpu_label);
    
    auto cpu_bar = new gui::ProgressBar();
    cpu_bar->set_position(10, 40);
    cpu_bar->set_value(35.0f);
    general_panel->add_child(cpu_bar);

    auto log_label = new gui::Label("Kernel Logs");
    log_label->set_position(10, 70);
    general_panel->add_child(log_label);

    auto log_area = new gui::TextArea();
    log_area->set_position(10, 100);
    log_area->set_size(480, 100);
    log_area->set_text("[0.000] ACOS Kernel v1.0.0 initializing...\n[0.001] PMM initialized\n[0.002] VMM initialized\n[0.003] Scheduler started");
    general_panel->add_child(log_area);

    // Personalization Tab
    auto theme_panel = new gui::Panel();
    tabs->add_tab("Appearance", theme_panel);

    auto bright_label = new gui::Label("Backlight Intensity");
    bright_label->set_position(10, 10);
    theme_panel->add_child(bright_label);

    auto bright_slider = new gui::Slider();
    bright_slider->set_position(10, 40);
    bright_slider->set_value(75.0f);
    theme_panel->add_child(bright_slider);

    auto theme_label = new gui::Label("Active Theme");
    theme_label->set_position(10, 80);
    theme_panel->add_child(theme_label);

    auto theme_combo = new gui::ComboBox();
    theme_combo->set_position(10, 110);
    theme_combo->add_item("Synthetic (Dark)");
    theme_combo->add_item("Obsidian");
    theme_combo->add_item("Light");
    theme_panel->add_child(theme_combo);

    auto wifi_switch = new gui::Switch("Blur Effects");
    wifi_switch->set_position(10, 160);
    wifi_switch->set_on(true);
    theme_panel->add_child(wifi_switch);

    m_display_btn.set_position(350, 400);
    m_theme_btn.set_position(450, 400);
    add_child(&m_display_btn);
    add_child(&m_theme_btn);
}

void Settings::on_display_clicked() {}
void Settings::on_theme_clicked() {}

} // namespace acos::apps
