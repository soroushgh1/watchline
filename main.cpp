#include "./src/dialogs/datepicker.h"
#include "./src/sections/test.h"
#include "./src/sections/usage.h"
#include "gdkmm/display.h"
#include "gtkmm/box.h"
#include "gtkmm/cssprovider.h"
#include "gtkmm/enums.h"
#include "gtkmm/grid.h"
#include "gtkmm/stylecontext.h"
#include <adwaita.h>
#include <gtkmm.h>
#include <memory>

class MainWindow : public Gtk::Window {

public:
  MainWindow() {
    set_title("Watchline");
    set_default_size(800, 600);
    set_child(main_grid);
    loadPanel(&panel, &main_grid, "side");
    panel.set_orientation(Gtk::Orientation::VERTICAL);
    loadCss();
    main_grid.get_style_context()->add_class("main_grid");

    usage_section = std::make_unique<UsageSection>(&main_grid, &panel);
    test_section = std::make_unique<TestSection>(&main_grid, &panel);
  }

  void loadCss() {

    auto css = Gtk::CssProvider::create();
    css->load_from_path("../style.css");

    Gtk::StyleContext::add_provider_for_display(
        Gdk::Display::get_default(), css,
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  }

  void loadPanel(Gtk::Box *panel, Gtk::Grid *main_grid,
                 std::string class_name) {

    panel->set_vexpand(true);
    panel->get_style_context()->add_class(class_name);
    main_grid->attach(*panel, 0, 0);
  }

private:
  Gtk::Grid main_grid;
  Gtk::Box panel;
  std::unique_ptr<TestSection> test_section;
  std::unique_ptr<UsageSection> usage_section;
};

int main(int argc, char *argv[]) {

  adw_init();

  auto app = Gtk::Application::create("org.gtkmm.example");

  return app->make_window_and_run<MainWindow>(argc, argv);
}
