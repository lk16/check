#ifndef CHECK_MOVE_HPP
#define CHECK_MOVE_HPP

#include <bitset>
#include <string> 

// http://dezlaren.home.xs4all.nl/opgaven/BordNummering.gif
//  EVERYTHING -1 ^^^^
struct move{
  
  // multiply by (-1) when trying to do a move for white
  static int walk[3] = { 4,5,6 };
  static int hit[2] = { 9,11 }
  
  static std::bitset<50> walk_allowed[3];

  static void init(){
    for(int i=0;i<3;i++){
      for(int p=0;p<50;p++){
        if( ((p/5)==((p+walk[i])/5)-1) && (p<50){
          move::walk_allowed[i].set(p);
        }
      }
    }
  }
  
};


#endif