#include "move.hpp"

int move::diff_walk[2][4];
int move::diff_capture[4];

std::bitset<50> move::is_left;
std::bitset<50> move::walk_possible[4];

void move::init(){
  for(int i=0;i<50;i++){
    is_left.set(i,(i/5)%2==1);
  }
  diff_walk[ROW_L][DIR_DL] = 4;
  diff_walk[ROW_L][DIR_DR] = 5;
  diff_walk[ROW_L][DIR_UL] = -6;
  diff_walk[ROW_L][DIR_UR] = -5;
  diff_walk[ROW_R][DIR_DL] = 5;
  diff_walk[ROW_R][DIR_DR] = 6;
  diff_walk[ROW_R][DIR_UL] = -5;
  diff_walk[ROW_R][DIR_UR] = -4;
  
  walk_possible[DIR_DL].set();
  walk_possible[DIR_DR].set();
  walk_possible[DIR_UL].set();
  walk_possible[DIR_UR].set();
  
  for(int i=0;i<5;i++){
    // top border
    walk_possible[DIR_UL].reset(i);
    walk_possible[DIR_UR].reset(i);
    
    // bottom border
    walk_possible[DIR_DL].reset(45+i);
    walk_possible[DIR_DR].reset(45+i);
    
    // left border
    walk_possible[DIR_DL].reset((10*i)+5);
    walk_possible[DIR_UL].reset((10*i)+5);
    
    // right border
    walk_possible[DIR_DR].reset((10*i)+4);
    walk_possible[DIR_UR].reset((10*i)+4);
    
  }
  
  diff_capture[DIR_UL] = -11;
  diff_capture[DIR_UR] = - 9;
  diff_capture[DIR_DL] =   9;
  diff_capture[DIR_DR] =  11;
  
}