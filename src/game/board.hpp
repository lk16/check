#ifndef CHECK_BOARD_HPP
#define CHECK_BOARD_HPP

#include <bitset>
#include <cassert>
#include <iostream>
#include <list>
#include <sstream>
#include <cstring>

#include "game/util.hpp"
#include "move.hpp"

struct board{
  std::bitset<50> discs[2];
  std::bitset<50> is_king;
  color turn;
    
  /// does NOTHING; call reset() to initialize
  board();
  
  /// copies a board
  board(const board& b);
  
  /// copies b into *this
  board& operator=(const board& b);
  
  /// checks for board equality
  bool operator==(const board& b) const;
  
  /// resets the board to starting position
  void reset();
  
  /// checks whether for *this and this->turn, field_id is a valid move
  /// WARNING: NOT EFFICIENT
  bool is_valid_move(int from,int to) const;
  
  /// performs move for *this and this->turn
  /// might crash if fed an invalid move
  /// WARNING: NOT EFFICIENT
  void do_move(int from,int to, board* out) const;
    
  /// gets all children from this board
  /// if out==NULL it is unchanged
  void get_children(board* out,int* move_count) const;
  
  /// prints this to standard output, mark moves for current turn with '.'
  void show() const;
  
};



inline board::board()
{
}

inline void board::reset(){
  
  /* wipe all discs of the board */
  discs[BLACK].reset();
  discs[WHITE].reset();
  is_king.reset();
  
  /* put starting pieces on board */
  for(int i=0;i<20;i++){
    discs[BLACK].set(i);
    discs[WHITE].set(30+i);
  }
  
  turn = WHITE;
  

}

inline board::board(const board& b)
{
  *this = b;
}



inline board& board::operator=(const board& b)
{
  discs[BLACK] = b.discs[BLACK];
  discs[WHITE] = b.discs[WHITE];
  is_king = b.is_king;
  turn = b.turn;
  return *this;
}

inline bool board::operator==(const board& b) const
{
  return true
    && b.discs[BLACK] == discs[BLACK]
    && b.discs[WHITE] == discs[WHITE]
    && b.is_king == is_king
    && b.turn==turn;
}


#endif
