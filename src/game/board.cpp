#include "board.hpp"

#define BIT_SHIFT(var,shift) (((shift)>0) ? ((var) << (shift)) : ((var) >> (-(shift))))


bool board::is_valid_move(int from,int to) const
{ 
  (void)from;
  (void)to;
  
  
  return false;
}

void board::do_move(int from,int to, board* out) const
{
  *out = *this;
  (void)from;
  (void)to;
  return;
}





void board::get_children(board* out,int* move_count) const
{
  int max_streak;
  get_max_king_capture_streak(out,move_count,&max_streak);
  if(max_streak==0){
    get_max_disc_capture_streak(out,move_count,&max_streak);
    if(max_streak==0){
      get_all_children(out,move_count);
    }
  }
}




void board::show() const
{
  int x,y;
  int index = 0;
  /* top line */
  std::cout << "+---------------------+\n";
  
  /* middle */
  for(y=0;y<10;y++){
    std::cout << "| ";
    for(x=0;x<10;x++){
      if((x%2==1) ^ (y%2==0)){
        std::cout << "  ";
        continue;
      }
      
      if(discs[BLACK].test(index)){
        std::cout << "\033[31;1mo\033[0m ";
      }
      else if(discs[WHITE].test(index)){
        std::cout << "\033[34;1mo\033[0m ";
      }
      else if(is_king[BLACK].test(index)){
        std::cout << "\033[31;1m@\033[0m ";
      }
      else if(is_king[WHITE].test(index)){
        std::cout << "\033[34;1m@\033[0m ";
      }
      else{
        std::cout << "  ";
      }
      index++;
    }
    std::cout << "|\n";
  }
  
  /* bottom line */
  std::cout << "+---------------------+\n";
}

void board::get_max_king_capture_streak(board* out, int* move_count, int* max_streak) const
{
  (void)out;
  NOT_IMPLEMENTED;
  *max_streak = *move_count = 0;
}

void board::get_max_disc_capture_streak(board* out, int* move_count, int* max_streak) const
{
  (void)out;
  NOT_IMPLEMENTED;
  *max_streak = *move_count = 0;
}

void board::get_all_children(board* out, int* move_count) const
{
  *move_count = 0;
  
  std::bitset<50> empty_fields = get_empty_fields();
  std::bitset<50> my_l_discs = discs[turn] & move::is_left;
  std::bitset<50> my_r_discs = discs[turn] & (~move::is_left);
  
  std::bitset<50> move_case[4];
  
  if(turn==BLACK){
    move_case[0] = (my_r_discs & move::walk_possible[DIR_DL] & BIT_SHIFT(empty_fields,-move::diff_walk[0][DIR_DL]));
    move_case[1] = (my_r_discs & move::walk_possible[DIR_DR] & BIT_SHIFT(empty_fields,-move::diff_walk[0][DIR_DR]));
    move_case[2] = (my_l_discs & move::walk_possible[DIR_DL] & BIT_SHIFT(empty_fields,-move::diff_walk[1][DIR_DL]));
    move_case[3] = (my_l_discs & move::walk_possible[DIR_DR] & BIT_SHIFT(empty_fields,-move::diff_walk[1][DIR_DR]));
  
    for(int i=0;i<2;i++){
      while(my_r_discs.any()){
        int index = find_first_set_64(my_r_discs.to_ulong())-1;
        assert(index!=-1);
        out[*move_count] = *this;
        out[*move_count].discs[turn].flip(index);
        out[*move_count].discs[turn].flip(index + move::diff_walk[0][i==0 ? DIR_DL : DIR_DR]);         (*move_count)++;
        my_r_discs.reset(index);
      }
    }
    for(int i=0;i<2;i++){
      while(my_l_discs.any()){
        int index = find_first_set_64(my_l_discs.to_ulong())-1;
        assert(index!=-1);
        out[*move_count] = *this;
        out[*move_count].discs[turn].flip(index);
        out[*move_count].discs[turn].flip(index + move::diff_walk[1][i==0 ? DIR_DL : DIR_DR]); 
        (*move_count)++;
        my_l_discs.reset(index);
      }
    }
  }
  else{
    assert(turn==WHITE);
    move_case[0] = (my_r_discs & move::walk_possible[DIR_UL] & BIT_SHIFT(empty_fields,-move::diff_walk[0][DIR_UL]));
    move_case[1] = (my_r_discs & move::walk_possible[DIR_UR] & BIT_SHIFT(empty_fields,-move::diff_walk[0][DIR_UR]));
    move_case[2] = (my_l_discs & move::walk_possible[DIR_UL] & BIT_SHIFT(empty_fields,-move::diff_walk[1][DIR_UL]));
    move_case[3] = (my_l_discs & move::walk_possible[DIR_UR] & BIT_SHIFT(empty_fields,-move::diff_walk[1][DIR_UR]));
  }
}
