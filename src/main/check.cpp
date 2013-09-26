#include <gtkmm.h>

#include "gui/main_window.hpp"

void run_debug(){
  board b;
  std::cout << b.get_stable_disc_count_diff(3) << std::endl;
}





int main(int argc,char **argv){
  Gtk::Main kit(argc,argv);
  main_window window;
  
  if(argc>=2){
    std::string argv1(argv[1]);
    if(argv1=="no-gui"){
      run_no_gui();
    }
    else if(argv1=="debug"){
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
