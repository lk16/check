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

int move::king_dist_max[4][50];
int move::king_dist_diff[2][4][9];


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
  
  king_dist_diff =
  { 
    { // is right
      {- 5,-11,-16,-22,-27,-33,-38,-44,-49}, // UL
      {- 4,- 9,-13,-18,-22,-27,-31,-36,-40}, // UR
      {  5,  9, 14, 18, 23, 27, 32, 36, 41}, // DL
      {  6, 11, 17, 22, 28, 33, 39, 44, 50}  // DR
    },
    {  // is left
      {- 6,-11,-17,-22,-28,-33,-39,-44,-50}, // UL
      {- 5,- 9,-14,-18,-23,-27,-32,-36,-41}, // UR
      {  4,  9, 13, 18, 22, 27, 31, 36, 40}, // DL
      {  5, 11, 16, 22, 27, 33, 38, 44, 49}  // DR
    }  
  };
  
  king_dist_max = {
 //  0                   1                   2                   3                   4
 //  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
    {0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,0,2,3,3,3,1,3,4,4,4,0,2,4,5,5,1,3,5,6,6,0,2,4,6,7,1,3,5,7,8,0,2,4,6,8}, // UL
    {0,0,0,0,0,1,1,1,1,1,2,2,2,2,0,3,3,3,3,1,4,4,4,2,0,5,5,5,3,1,6,6,4,2,0,7,7,5,3,1,8,6,4,2,0,9,7,5,3,1}, // UR
    {1,3,5,7,9,0,2,4,6,8,1,3,5,7,7,0,2,4,6,6,1,3,5,5,5,0,2,4,4,4,1,3,3,3,3,0,2,2,2,2,1,1,1,1,1,0,0,0,0,0}, // DL
    {8,6,4,2,0,8,7,5,3,1,7,6,4,2,0,6,6,5,3,1,5,5,4,2,0,4,4,4,3,1,3,3,3,2,0,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0}  // DR
    
  };
  
  
}