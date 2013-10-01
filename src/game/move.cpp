#include "move.hpp"

std::bitset<50> move::is_left;

std::bitset<50> move::up4;
std::bitset<50> move::up5;
std::bitset<50> move::up6;
std::bitset<50> move::down4;
std::bitset<50> move::down5;
std::bitset<50> move::down6;

void move::init(){
  for(int i=0;i<50;i++){
    is_left.set(i,(i/5)%2==1);
  }
 
  up5.set();
  down5.set();
  
  up4 = down6 = is_left;
  up6 = down4 = ~is_left;
  
  for(int i=0;i<5;i++){
    
    // top line
    down4.reset(i);
    down5.reset(i);
    down6.reset(i);
    
    // bottom line
    up4.reset(45+i);
    up5.reset(45+i);
    up6.reset(45+i);
    
    // leftmost of the left
    up4.reset(5+(10*i));
    down6.reset(5+(10*i));
    
    // rightmost of the right
    up6.reset(4+(10*i));
    down4.reset(4+(10*i));
    
  }
  
}