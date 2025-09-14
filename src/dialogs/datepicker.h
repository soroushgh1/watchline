#ifndef DATEPICKER
#define DATEPICKER

#include <gtkmm.h>

class DatePicker : public Gtk::Dialog {
public:
  DatePicker(Gtk::Window &parent);

  int get_day() const;
  int get_month() const;
  int get_year() const;

private:
  Gtk::Calendar calendar;
};

#endif
