#include <gtkmm.h>

#include "gui/main_window.hpp"
#include "game/move.hpp"


void run_debug(){
  board b;
  b.reset();
  b.show();
  move::init();
  for(int i=0;i<4;i++){
    show_bitset(move::walk_possible[i]);
  }
}





int main(int argc,char **argv){
  Gtk::Main kit(argc,argv);
  main_window window;
  
  if(argc>=2){
    std::string argv1(argv[1]);
    if(argv1=="debug"){
      run_debug();
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
