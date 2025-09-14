#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/grid.h"
#include "gtkmm/label.h"
#include "gtkmm/spinner.h"

#ifndef TEST
#define TEST

class TestSection {
public:
  TestSection(Gtk::Grid *win_grid, Gtk::Box *sidebar);
  void loadLabel(Gtk::Label *label, std::string class_name);
  void loadDescription(Gtk::Label *description);
  void loadButton(Gtk::Button *btn);
  void loadResults();
  void testInternet();
  void onPanelBtnClicked();
  void onStartBtnClicked();

private:
  Gtk::Grid *maingrid;
  Gtk::Grid test_section_grid;
  Gtk::Button panel_btn;
  Gtk::Box *sidebar;

  Gtk::Label title;
  Gtk::Label description;
  Gtk::Button start_btn;

  Gtk::Grid result_grid;
  Gtk::Label download_speed;
  Gtk::Label upload_speed;
  Gtk::Label ping;
  Gtk::Label server;

  Gtk::Spinner spinner;
};

#endif
