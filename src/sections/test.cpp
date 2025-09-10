#include "../sections/test.h"
#include "../../external/json.hpp"
#include "../helpers/exec.h"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/grid.h"
#include "gtkmm/label.h"
#include "gtkmm/widget.h"
#include "sigc++/functors/mem_fun.h"
#include <giomm.h>
#include <glibmm.h>
#include <glibmm/main.h>
#include <string>
#include <thread>

using json = nlohmann::json;

TestSection::TestSection(Gtk::Grid *win_grid, Gtk::Box *sidebar_ptr) {
  maingrid = win_grid;
  sidebar = sidebar_ptr;

  sidebar->append(panel_btn);
  panel_btn.set_label("Test");
  panel_btn.set_margin(3);
  panel_btn.get_style_context()->add_class("test_panel_btn");
  panel_btn.signal_clicked().connect(
      sigc::mem_fun(*this, &TestSection::onPanelBtnClicked));

  test_section_grid.attach(title, 0, 0);
  test_section_grid.attach(description, 0, 1);
  test_section_grid.attach(start_btn, 0, 2);
  test_section_grid.attach(result_grid, 0, 3);

  start_btn.signal_clicked().connect(
      sigc::mem_fun(*this, &TestSection::onStartBtnClicked));

  result_grid.attach(download_speed, 0, 0);
  result_grid.attach(upload_speed, 0, 1);
  result_grid.attach(ping, 0, 2);
  result_grid.attach(server, 0, 3);

  result_grid.set_halign(Gtk::Align::CENTER);
  result_grid.set_valign(Gtk::Align::START);
  result_grid.set_vexpand(true);
  result_grid.set_margin_bottom(30);
  result_grid.set_row_spacing(15);
}

void TestSection::loadLabel(Gtk::Label *label) {

  label->set_label("Test Your Internet Performance");
  label->set_halign(Gtk::Align::CENTER);
  label->set_hexpand(true);
  label->get_style_context()->add_class("test_section_title");
  label->set_margin_top(70);
}

void TestSection::loadDescription(Gtk::Label *description) {

  description->set_label(
      "1. Turn off your VPN for realistic results\n"
      "2. Close background windows and tasks before testing\n"
      "3. Start the test during low traffic hours\n");
  description->get_style_context()->add_class("test_section_description");
  description->set_valign(Gtk::Align::START);
  description->set_margin_start(80);
  description->set_margin_top(70);
}

void TestSection::loadButton(Gtk::Button *btn) {

  btn->set_label("Start Testing");
  btn->set_hexpand(false);
  btn->set_halign(Gtk::Align::CENTER);
  btn->set_vexpand(true);
  btn->set_valign(
      Gtk::Align::START); // or CENTER or END depending on what you want
  btn->set_margin_top(25);
  btn->get_style_context()->add_class("suggested-action");
  btn->get_style_context()->add_class("test_section_startbtn");
}

void TestSection::loadResults() {

  std::thread([this] {
    json results;
    std::string results_json = exec("speedtest-cli --json");
    results = json::parse(results_json);
    int upload = results["upload"].get<int>();
    int download = results["download"].get<int>();
    int ping = results["ping"].get<int>();
    std::string name = results["server"]["name"].get<std::string>();
    std::string country = results["server"]["country"].get<std::string>();

    Glib::signal_idle().connect_once([this, upload, download, ping, name,
                                      country] {
      this->upload_speed.set_label(
          "Upload speed is: " + std::to_string(upload / 1'048'576.0) + " MB/s");
      this->upload_speed.get_style_context()->add_class(
          "test_section_uploadspeed");
      this->download_speed.set_label(
          "Download speed is: " + std::to_string(download / 1'048'576.0) +
          " MB/s");
      this->download_speed.get_style_context()->add_class(
          "test_section_downloadspeed");
      this->ping.set_label("Ping is: " + std::to_string(ping) + " ms");
      this->ping.get_style_context()->add_class("test_section_ping");
      this->server.set_label("Server located in: " + country + "/" + name);
      this->server.get_style_context()->add_class("test_section_server");
      this->result_grid.get_style_context()->add_class(
          "test_section_resultgrid");
    });
  }).detach();
}

void TestSection::onPanelBtnClicked() {

  loadLabel(&title);
  loadDescription(&description);
  loadButton(&start_btn);

  for (Gtk::Widget *widget : maingrid->get_children()) {
    if (widget == sidebar)
      continue;

    maingrid->remove(*widget);
  }

  maingrid->attach(test_section_grid, 1, 0);
}

void TestSection::onStartBtnClicked() { loadResults(); }
