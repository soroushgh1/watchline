#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/comboboxtext.h"
#include "gtkmm/enums.h"
#include "gtkmm/label.h"
#include <gtkmm.h>
#ifndef USAGE
#define USAGE

struct OptionAndLabel {
  Gtk::Box container{Gtk::Orientation::HORIZONTAL};
  Gtk::ComboBoxText option;
  Gtk::Label label;

  OptionAndLabel() {
    container.append(label);
    container.append(option);
  }
};

struct PopBtnAndLabel {
  Gtk::Box container{Gtk::Orientation::HORIZONTAL};
  Gtk::Button button;
  Gtk::Label label;

  PopBtnAndLabel() {
    container.append(label);
    container.append(button);
  }
};

class UsageSection {
public:
  UsageSection(Gtk::Grid *win_grid, Gtk::Box *sidebar);
  void loadLabel(Gtk::Label *label, std::string class_name);
  void loadReport();
  void onPanelBtnClicked();

private:
  Gtk::Grid *maingrid;
  Gtk::Box *panel;
  Gtk::Grid usage_section_grid;

  Gtk::Button panel_btn;

  Gtk::Label title;
  OptionAndLabel recent_period;
  PopBtnAndLabel choose_period;
  Gtk::Button start_report;
  Gtk::Box timerow{Gtk::Orientation::HORIZONTAL};
};

#endif
