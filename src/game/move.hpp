#ifndef CHECK_MOVE_HPP
#define CHECK_MOVE_HPP

#include <bitset>

enum{
  ROW_L = 1, // refers to rows 0,2,4,6,8
  ROW_R = 0  // refers to rows 1,3,5,7,9
};

enum{
  DIR_UL = 0,
  DIR_UR = 1,
  DIR_DL = 2,
  DIR_DR = 3
};



// http://dezlaren.home.xs4all.nl/opgaven/BordNummering.gif
//  EVERYTHING -1 ^^^^
struct move{
  
  // has only set bits in rows 1,3,5,7,9 (using zero-based row counting)
  static std::bitset<50> is_left;
  
  /// all data for BLACK, multiply by (-1) for data on WHITE
  
  
  // contains difference in index of walk in any direction, per row line type
  // example use: move::diff_walk[is_left.test(0)][DIR_DR];
  static int diff_walk[2][4];
  
  // contains difference in index of capturing in any direction
  // row line types do not matter
  static int diff_capture[4];
  
  // can i walk in this direction from this field?
  // example use: move::walk_possible[DIR_UL].test(0)
  static std::bitset<50> walk_possible[4];
  
  
  // initialize all static move values
  static void init();
  
};


#endif