#ifndef CHECK_MOVE_HPP
#define CHECK_MOVE_HPP

#include <bitset>

// http://dezlaren.home.xs4all.nl/opgaven/BordNummering.gif
//  EVERYTHING -1 ^^^^
struct move{
  
  // multiply by (-1) when trying to do a move for white
  static int walk[3];
  static int capture[4];
  
  static std::bitset<50> walk_possible[3];
  static std::bitset<50> capture_possible[4];

  static void init(){
    move::walk[0] = 4;
    move::walk[1] = 5;
    move::walk[2] = 6;
    
    move::capture[0] = -11;
    move::capture[0] = - 9;
    move::capture[0] =   9;
    move::capture[0] =  11;
    
    for(int p=0;p<50;p++){
      int my_row = p/5;
      for(int i=0;i<3;i++){
        int test_row = (p+walk[i])/5;
        if((test_row==my_row+1) && (test_row<10)){
          move::walk_possible[i].set(p);
        }
      }
      for(int i=0;i<4;i++){
        int test_row = (p+capture[i])/5;
        if((test_row==my_row+2) && (test_row<10) && (test_row>=0)){
          move::capture_possible[i].set(p);
        }
      }
    }
  }
  
};


#endif