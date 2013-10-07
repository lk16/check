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
  std::bitset<50> kings[2];
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
  
  /// returns a bitset with only bits corresponding to empty fields set
  std::bitset<50> get_empty_fields() const;
  
  /// checks whether for *this and this->turn, field_id is a valid move
  /// WARNING: NOT EFFICIENT
  bool is_valid_move(int from,int to) const;
  
  /// performs move for *this and this->turn
  /// might crash if fed an invalid move
  /// WARNING: NOT EFFICIENT
  /// WARNING: will not perform all captures but at most one
  
  void do_move(int from,int to, board* out) const;
    
  /// gets all children from this board
  /// if out==NULL it is unchanged
  void get_children(board* out,int* move_count) const;
  
  /// out will point to an array of boards which arethe current board after doing
  /// all different move sequences from the current board with a king 
  /// resulting in the maximum possible capture streak >=1
  /// number will contain the number of found boards
  /// returns possibly increased out pointer
  board* get_max_king_capture_streak(board* out) const;
  
  /// out will point to an array of boards which arethe current board after doing
  /// all different move sequences from the current board with a normal disc 
  /// resulting in the maximum possible capture streak >=1
  /// number will contain the number of found boards
  /// returns possibly increased out pointer
  board* get_max_disc_capture_streak(board* out) const;
  
  /// adds all possible end states of capture streaks from disc start in this
  /// WARNING: choose LEFT or RIGHT version based on is.left.test(start)
  /// returns possibly increased out pointer
  board* get_all_successive_disc_captures_left(board* out,int start) const;
  board* get_all_successive_disc_captures_right(board* out,int start) const;
  
  /// adds all possible end states of capture streaks from king start in this
  /// returns possibly increased out pointer
  board* get_all_successive_king_captures(board* out,int start) const;
  
  /// switches the turn
  void switch_turn();
  
  /// puts ALL children in out
  /// number will contain the number of found boards
  /// returns possibly increased out pointer
  board* get_all_children_no_capture(board* out) const;
  
  /// prints board state to stdout
  void show() const;
  
};



inline board::board()
{
}

inline void board::reset(){
  
  /* wipe all discs of the board */
  discs[BLACK].reset();
  discs[WHITE].reset();
  kings[BLACK].reset();
  kings[WHITE].reset();
  
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
  kings[BLACK] = b.kings[BLACK];
  kings[WHITE] = b.kings[WHITE];
  turn = b.turn;
  return *this;
}

inline bool board::operator==(const board& b) const
{
  return true
    && b.discs[BLACK] == discs[BLACK]
    && b.discs[WHITE] == discs[WHITE]
    && b.kings[BLACK] == kings[BLACK]
    && b.kings[WHITE] == kings[WHITE]
    && b.turn==turn;
}

inline std::bitset<50> board::get_empty_fields() const
{
  return ~(discs[BLACK] | discs[WHITE] | kings[BLACK] | kings[WHITE]);
}

inline void board::switch_turn()
{
  turn = opponent(turn);
}


#endif
