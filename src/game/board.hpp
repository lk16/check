#ifndef CHECK_BOARD_HPP
#define CHECK_BOARD_HPP

#include <bitset>
#include <cassert>
#include <iostream>
#include <list>
#include <sstream>
#include <cstring>

#include "game/util.hpp"

struct board{
  std::bitset<50> discs[2];
  std::bitset<50> is_king[2];
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
  void do_move(int field_id,board* out) const;
  
  /// out will represent a bitset of which each set bit represents a square
  /// that COULD BE a valid move
  void get_possible_moves(std::bitset<50> *out) const;
  
  /// gets all children from this board
  /// if out==NULL it is unchanged
  void get_children(board* out,int* move_count) const;
  
  /// prints this to standard output, mark moves for current turn with '.'
  void show() const;
  
  /// returns disc count difference positive means white has more
  int get_disc_diff() const;
  
  /// tries a move, if not valid, returns false
  //bool try_move(int field_id,std::bitset<64>* undo_data);
  
  /// recovers a board state before move field_id, with flipped discs in undo_data 
  // void undo_move(int field_id,std::bitset<64>* undo_data); 
  
};



inline board::board()
{
}

inline void board::reset(){
  
  /* wipe all discs of the board */
  discs[BLACK].reset();
  discs[WHITE].reset();
  
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

inline void board::set_all()
{
  discs[BLACK].set();
  discs[WHITE].set();
}



inline board& board::operator=(const board& b)
{
  discs[BLACK] = b.discs[BLACK];
  discs[WHITE] = b.discs[WHITE];
  is_king[BLACK] = b.is_king[BLACK];
  is_king[WHITE] = b.is_king[WHITE];
  turn = b.turn;
  return *this;
}

inline bool board::operator==(const board& b) const
{
  return true
    && b.discs[BLACK] == discs[BLACK]
    && b.discs[WHITE] == discs[WHITE]
    && b.is_king[BLACK] == is_king[BLACK]
    && b.is_king[WHITE] == is_king[WHITE]
    && b.turn==turn;
}


#endif
