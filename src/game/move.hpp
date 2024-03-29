#ifndef CHECK_MOVE_HPP
#define CHECK_MOVE_HPP

#include <bitset>

enum{
  ROW_L = 1, // refers to rows 0,2,4,6,8
  ROW_R = 0  // refers to rows 1,3,5,7,9
};


//  http://pitkit.files.wordpress.com/2012/11/dambord-nummering4.png
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
  
  static std::bitset<50> up9;
  static std::bitset<50> up11;
  static std::bitset<50> down9;
  static std::bitset<50> down11;
  
  
  static std::bitset<50> border_top;
  static std::bitset<50> border_bottom;
  static std::bitset<50> border_left;
  static std::bitset<50> border_right;
  
  // 1st index: direction
  // 2nd index: move id
  static int king_dist_max[4][50];
  
  // 1st index: is_left ?
  // 2nd index: direction
  // 3rd index distance
  static int king_dist_diff[2][4][9];

  // initialize all static move values
  static void init();
  
};


#endif