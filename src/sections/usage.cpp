#include "usage.h"
#include "gtkmm/enums.h"
#include "gtkmm/label.h"
#include "sigc++/functors/mem_fun.h"
#include <gtkmm.h>

UsageSection::UsageSection(Gtk::Grid *win_grid, Gtk::Box *sidebar) {
  maingrid = win_grid;
  panel = sidebar;

  panel_btn.set_label("Usage");
  panel_btn.set_margin(3);
  panel_btn.get_style_context()->add_class("usage_panel_btn");
  panel->append(panel_btn);

  panel_btn.signal_clicked().connect(
      sigc::mem_fun(*this, &UsageSection::onPanelBtnClicked));

  loadLabel(&title, "usage_section_title");
  loadReport();
  usage_section_grid.attach(title, 0, 0);
}

void UsageSection::loadLabel(Gtk::Label *label, std::string class_name) {
  label->set_label("Track Your Internet Usage");
  label->set_hexpand(true);
  label->set_halign(Gtk::Align::CENTER);
  label->set_margin_top(50);
  label->get_style_context()->add_class(class_name);
}

void UsageSection::onPanelBtnClicked() {

  for (Gtk::Widget *widget : maingrid->get_children()) {
    if (widget == panel)
      continue;
    maingrid->remove(*widget);
  }

  maingrid->attach(usage_section_grid, 1, 0);
}

void UsageSection::loadReport() {

  recent_period.label.set_label("Recent:");
  recent_period.label.set_margin_end(10);
  recent_period.label.get_style_context()->add_class("usage_recent_label");

  choose_period.label.set_label("Choose:");
  choose_period.label.set_margin_end(10);
  choose_period.label.get_style_context()->add_class("usage_choose_label");

  recent_period.option.append("Today");
  recent_period.option.append("This Week");
  recent_period.option.append("This Month");

  start_report.set_label("Check");
  start_report.get_style_context()->add_class("usage_startreport_button");
  start_report.get_style_context()->add_class("suggested-action");

  recent_period.option.get_style_context()->add_class("usage_recent_option");
  choose_period.button.get_style_context()->add_class("usage_choose_button");

  recent_period.container.set_margin_end(23);
  choose_period.container.set_margin_end(23);

  timerow.set_hexpand(true);
  timerow.set_halign(Gtk::Align::CENTER);

  timerow.append(recent_period.container);
  timerow.append(choose_period.container);
  timerow.append(start_report);
  timerow.set_margin_top(40);

  usage_section_grid.attach(timerow, 0, 1);
}
