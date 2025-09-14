#include "datepicker.h"

DatePicker::DatePicker(Gtk::Window &parent)
    : Gtk::Dialog("Select a Date", parent) {
  set_default_size(300, 300);
  set_transient_for(parent);
  set_modal(true);

  add_button("Cancel", Gtk::ResponseType::CANCEL);
  add_button("OK", Gtk::ResponseType::OK);

  auto *content = get_content_area();
  content->append(calendar);

  show();
}

int DatePicker::get_day() const { return calendar.get_day(); }
int DatePicker::get_month() const { return calendar.get_month() + 1; }
int DatePicker::get_year() const { return calendar.get_year(); }
