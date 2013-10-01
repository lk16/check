#ifndef CHECK_MOVE_HPP
#define CHECK_MOVE_HPP

#include <bitset>

enum{
  ROW_L = 1, // refers to rows 0,2,4,6,8
  ROW_R = 0  // refers to rows 1,3,5,7,9
};

// http://dezlaren.home.xs4all.nl/opgaven/BordNummering.gif
//  EVERYTHING -1 ^^^^
struct move{
  
  // has only set bits in rows 1,3,5,7,9 (using zero-based row counting)
  static std::bitset<50> is_left;
  
  // WARNING: up in index is down on the board !!
  // bitsets for allowed difference in index to get to a "neighbor field"
                                // color  left/right
                                //------------------
  static std::bitset<50> up4;   // black  left
  static std::bitset<50> up5;   // black  both
  static std::bitset<50> up6;   // black  right
  static std::bitset<50> down4; // white  right
  static std::bitset<50> down5; // white  both  
  static std::bitset<50> down6; // white  left
  
  static std::bitset<50> border_top;
  static std::bitset<50> border_bottom;
  static std::bitset<50> border_left;
  static std::bitset<50> border_right;
  


  // initialize all static move values
  static void init();
  
};


#endif