#include "move.hpp"

std::bitset<50> move::is_left;

std::bitset<50> move::up4;
std::bitset<50> move::up5;
std::bitset<50> move::up6;
std::bitset<50> move::down4;
std::bitset<50> move::down5;
std::bitset<50> move::down6;

std::bitset<50> move::border_left;
std::bitset<50> move::border_right;
std::bitset<50> move::border_top;
std::bitset<50> move::border_bottom;

void move::init(){
  for(int i=0;i<50;i++){
    is_left.set(i,(i/5)%2==1);
  }
 
  up5.set();
  down5.set();
  
  up4 = down6 = is_left;
  up6 = down4 = ~is_left;
  
  for(int i=0;i<5;i++){
    
    border_top.set(i);
    
    border_bottom.set(45+i);
    
    border_left.set(5+(10*i));
    
    border_right.set(4+(10*i));
    
  }
  down4 &= (~border_top);
  down4 &= (~border_right);
  
  down5 &= (~border_top);
  
  down6 &= (~border_left);
  down6 &= (~border_top);
  
  up4 &= (~border_bottom);
  up4 &= (~border_left);
  
  up5 &= (~border_bottom);
  
  up6 &= (~border_bottom);
  up6 &= (~border_right);
  
}