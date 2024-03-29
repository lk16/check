#include <gtkmm.h>

#include "gui/main_window.hpp"
#include "game/move.hpp"


void testing_area(){
  board b;
  b.reset();
  b.is_valid_move(25,30);
  
  
  return;
  
  board children[100];
  int child_count;
  b.get_children(children,&child_count);
  for(int i=0;i<child_count;i++){
    children[i].show();
  }
  std::cout << "child_count = " << child_count << '\n';
  
  
}





int main(int argc,char **argv){
  Gtk::Main kit(argc,argv);
  main_window window;
  
  // this is ugly, but at least it won't be forgotten
  move::init();
  
  
  if(argc>=2){
    std::string argv1(argv[1]);
    if(argv1=="testing"){
      testing_area();
    }
    else{
      std::cout << "Invalid parameter: " << argv1 << '\n';
    }
  }
  else{
    Gtk::Main::run(window);
  }
  return 0;
}
