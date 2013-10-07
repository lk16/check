#include "gui_base/clickable_image.hpp"

clickable_image::clickable_image(main_window* par, int _field_id, const std::string& imagefile): 
  Gtk::EventBox(),
  image(imagefile),
  field_id(_field_id),
  parent(par)
{
  add(image);
  show_all_children();
}

bool clickable_image::on_button_press_event(GdkEventButton* _event)
{
  (void)_event;
  
  std::cout << "Field " << field_id << " was clicked\n";
  
  if(field_id>=-1 && field_id<=50){
    parent->control.on_human_click(field_id);
  }
  
  
  return true;
}

void clickable_image::set(const std::string& filename)
{
  image.set(filename);
}
