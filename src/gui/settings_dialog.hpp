#ifndef CHECK_SETTINGS_DIALOG_HPP
#define CHECK_SETTINGS_DIALOG_HPP

#include <gtkmm/dialog.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/scale.h>
#include <gtkmm/frame.h>
#include <gtkmm/box.h>

class settings_dialog:
  public Gtk::Dialog
{
  Gtk::RadioButton radio_w_bot,radio_w_human,radio_b_bot,radio_b_human;
  Gtk::RadioButtonGroup radio_group_w,radio_group_b;
  Gtk::HScale scale_w,scale_b;
  Gtk::Frame frame_w,frame_b;
  Gtk::VBox vbox_w,vbox_b,big_vbox;
  Gtk::Button ok_button;

public:
  // use -1 for human
  settings_dialog(Gtk::Window& parent,int black_level,int white_level);
  
  void collect_data(int* black_level,int* white_level);
  
  
};

#endif