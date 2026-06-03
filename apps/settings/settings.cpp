#include "settings.h"
#include <ui/theme.h>
#include <ui/label.h>
#include <ui/button.h>
#include <ui/progressbar.h>
#include <ui/checkbox.h>
#include <ui/slider.h>
#include <ui/layout.h>
#include <ui/tabwidget.h>
#include <ui/panel.h>
#include <ui/switch.h>
#include <ui/combobox.h>
#include <ui/textarea.h>

namespace acos::apps {

Settings::Settings()
    : ui::WindowWidget("System Settings", 50, 50, 550, 450),
      m_display_btn("Apply"), m_theme_btn("Cancel") {
    
    auto tabs = new ui::TabWidget();
    tabs->set_position(10, 10);
    tabs->set_size(530, 330);
    add_child(tabs);

    // Activity Tab
    auto general_panel = new ui::Panel();
    tabs->add_tab("Activity", general_panel);
    
    auto cpu_label = new ui::Label("Kernel Activity");
    cpu_label->set_position(10, 10);
    general_panel->add_child(cpu_label);
    
    auto cpu_bar = new ui::ProgressBar();
    cpu_bar->set_position(10, 40);
    cpu_bar->set_value(35.0f);
    general_panel->add_child(cpu_bar);

    auto log_label = new ui::Label("Kernel Logs");
    log_label->set_position(10, 70);
    general_panel->add_child(log_label);

    auto log_area = new ui::TextArea();
    log_area->set_position(10, 100);
    log_area->set_size(480, 100);
    log_area->set_text("[0.000] ACOS Kernel v1.0.0 initializing...\n[0.001] PMM initialized\n[0.002] VMM initialized\n[0.003] Scheduler started");
    general_panel->add_child(log_area);

    // Personalization Tab
    auto theme_panel = new ui::Panel();
    tabs->add_tab("Appearance", theme_panel);

    auto bright_label = new ui::Label("Backlight Intensity");
    bright_label->set_position(10, 10);
    theme_panel->add_child(bright_label);

    auto bright_slider = new ui::Slider();
    bright_slider->set_position(10, 40);
    bright_slider->set_value(75.0f);
    theme_panel->add_child(bright_slider);

    auto theme_label = new ui::Label("Active Theme");
    theme_label->set_position(10, 80);
    theme_panel->add_child(theme_label);

    auto theme_combo = new ui::ComboBox();
    theme_combo->set_position(10, 110);
    theme_combo->add_item("Synthetic (Dark)");
    theme_combo->add_item("Obsidian");
    theme_combo->add_item("Light");
    theme_panel->add_child(theme_combo);

    auto wifi_switch = new ui::Switch("Blur Effects");
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
