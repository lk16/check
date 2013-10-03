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





void board::get_children(board* out_begin,int* move_count) const
{
  board* out_end;
  
  out_end = get_max_king_capture_streak(out_begin);
  if(out_begin == out_end){
    out_end = get_max_disc_capture_streak(out_begin);
    if(out_begin == out_end){
      out_end = get_all_children_no_capture(out_begin);
    }
  }
  
  *move_count = (out_end - out_begin);
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
      else if(kings[BLACK].test(index)){
        std::cout << "\033[31;1m@\033[0m ";
      }
      else if(kings[WHITE].test(index)){
        std::cout << "\033[34;1m@\033[0m ";
      }
      else{
        std::cout << "- ";
      }
      index++;
    }
    std::cout << "|\n";
  }
  
  /* bottom line */
  std::cout << "+---------------------+\n";
}

board* board::get_max_king_capture_streak(board* out_end) const
{
  board* out_begin = out_end;
  color opp = opponent(turn);
  
  std::bitset<50> inspected;
  
  inspected = kings[turn] & move::is_left;
  while(inspected.any()){
    int index = find_first_set_64((inspected).to_ulong()) - 1;
    assert(index!=-1);
    out_end = get_all_successive_king_captures(out_end,index);
    inspected.reset(index);
  }
  
  int count = out_end-out_begin;
  
  
  int fill_count = 0;
  int opp_field_count = (int)((discs[opp] | kings[opp]).count());
  int max_streak = 0;
  
  for(int i=0;i<count;i++){    
    int streak = opp_field_count - ((out_begin+i)->discs[opp] | (out_begin+i)->kings[opp]).count();
    if(streak == max_streak){
      *(out_begin+fill_count) = *(out_begin+i);
      fill_count++;
    }
    else if(streak > max_streak){
      max_streak = streak;
      *out_begin = *(out_begin+i);
      fill_count = 1;
    }
  }
  
  return out_end;
}

board* board::get_all_successive_king_captures(board* out, int start) const
{
  std::bitset<50> my_fields  = discs[turn] | kings[turn];
  std::bitset<50> empty_fields = get_empty_fields();
  std::bitset<50> opp_fields = discs[opponent(turn)] | kings[opponent(turn)];
  
  
  bool is_left = move::is_left.test(start);
  
  for(int dir=0;dir<4;dir++){
    
    // make sure we dont capture twice per direction per recursive call
    bool captured_yet = false;
    
    
    int step_size = 0;
    while(step_size<move::king_dist_max[dir][start]){
      const int tested  = start + move::king_dist_diff[is_left][dir][step_size];
      
      // bump into one of my own disc
      if(my_fields.test(tested)){
        // can not proceed this direction
        break;
      }
      
      // bump into opponent discs
      // can only capture if (1), (2) AND (3) hold:
      // (1) disc bumped into is not next to border of board in walking direction
      // (2) no disc directly behind it
      // (3) no disc captured yet in this recursive call
      if(opp_fields.test(tested)
        && (move::king_dist_max[dir][start]!=(step_size+1)) // condition (1)
        && (!captured_yet) // condition (3)
      ){
        
        const int king_spot = start + move::king_dist_diff[is_left][dir][step_size+1];
        
        
        // condition (2) does not hold
        if(!empty_fields.test(king_spot)){
          // can not proceed this direction
          break;
        }
        
        // we can capture!
        *out = *this;
        out->kings[turn] ^= ((1ul << start) | (1ul << king_spot));
        out->discs[opponent(turn)].reset(tested);
        out->kings[opponent(turn)].reset(tested);
        out++;
        captured_yet = true;
      }
      
      // try walking one step furthur in same direction
      step_size = step_size + 1;
    }
  }
  return out;
}






board* board::get_max_disc_capture_streak(board* out_end) const
{
  board* out_begin = out_end;
  color opp = opponent(turn);
  
  std::bitset<50> inspected;
  
  // test left fields
  inspected = discs[turn] & move::is_left;
  while(inspected.any()){
    int index = find_first_set_64((inspected).to_ulong()) - 1;
    assert(index!=-1);
    out_end = get_all_successive_disc_captures_left(out_end,index);
    inspected.reset(index);
  }
  
  // test right fields
  inspected = discs[turn] & (~move::is_left);
  while(inspected.any()){
    int index = find_first_set_64((inspected).to_ulong()) - 1;
    assert(index!=-1);
    out_end = get_all_successive_disc_captures_right(out_end,index);
    inspected.reset(index);
  }
  
  int count = out_end-out_begin;
  
  int fill_count = 0;
  int opp_field_count = (int)((discs[opp] | kings[opp]).count());
  int max_streak = 0;
  
  for(int i=0;i<count;i++){    
    int streak = opp_field_count - ((out_begin+i)->discs[opp] | (out_begin+i)->kings[opp]).count();
    if(streak == max_streak){
      *(out_end+fill_count) = *(out_begin+i);
      fill_count++;
    }
    else if(streak > max_streak){
      max_streak = streak;
      *out_begin = *(out_begin+i);
      fill_count = 1;
    }
  }
  
  return out_end;
}

board* board::get_all_successive_disc_captures_left(board* out, int start) const
{
  assert(discs[turn].test(start));
  
  const std::bitset<50> opp_fields = discs[opponent(turn)] | kings[opponent(turn)];
  board* out_start = out;
  
  board child;
  
  
  // Up Left
  if((move::down11 & (opp_fields << 6)).test(start)){
    child = *this;
    child.discs[turn] ^= ((1ul << start) | (1ul << (start-11)));
    child.discs[opponent(turn)].reset(start-6);
    child.kings[opponent(turn)].reset(start-6);
    out = child.get_all_successive_disc_captures_left(out,start-11);
  }
  // Up Right
  if((move::down9 & (opp_fields << 5)).test(start)){
    child = *this;
    child.discs[turn] ^= ((1ul << start) | (1ul << (start-9)));
    child.discs[opponent(turn)].reset(start-5);
    child.kings[opponent(turn)].reset(start-5);
    out = child.get_all_successive_disc_captures_left(out,start-9);
  }
  
  // Down Left
  if((move::up9 & (opp_fields >> 4)).test(start)){
    child = *this;
    child.discs[turn] ^= ((1ul << start) | (1ul << (start+9)));
    child.discs[opponent(turn)].reset(start+4);
    child.kings[opponent(turn)].reset(start+4);
    out = child.get_all_successive_disc_captures_left(out,start+9);
  }
  
  // Down Right
  if((move::up11 & (opp_fields >> 5)).test(start)){
    child = *this;
    child.discs[turn] ^= ((1ul << start) | (1ul << (start+11)));
    child.discs[opponent(turn)].reset(start+5);
    child.kings[opponent(turn)].reset(start+5);
    out = child.get_all_successive_disc_captures_left(out,start+11);
  }
  
  if(out == out_start){
    *out = *this;
    out++;
  }
  return out;
}

board* board::get_all_successive_disc_captures_right(board* out_begin, int start) const
{
  assert(discs[turn].test(start));
  
  const std::bitset<50> opp_fields = discs[opponent(turn)] | kings[opponent(turn)];
  board* out_end = out_begin;
  
  board child;
  
  
  // Up Left
  if((move::down11 & (opp_fields << 5)).test(start)){
    child = *this;
    child.discs[turn] ^= ((1ul << start) | (1ul << (start-11)));
    child.discs[opponent(turn)].reset(start-5);
    child.kings[opponent(turn)].reset(start-5);
    out_end = child.get_all_successive_disc_captures_right(out_end,start-11);
  }
  // Up Right
  if((move::down9 & (opp_fields << 4)).test(start)){
    child = *this;
    child.discs[turn] ^= ((1ul << start) | (1ul << (start-9)));
    child.discs[opponent(turn)].reset(start-4);
    child.kings[opponent(turn)].reset(start-4);
    out_end = child.get_all_successive_disc_captures_right(out_end,start-9);
  }
  
  // Down Left
  if((move::up9 & (opp_fields >> 5)).test(start)){
    child = *this;
    child.discs[turn] ^= ((1ul << start) | (1ul << (start+9)));
    child.discs[opponent(turn)].reset(start+5);
    child.kings[opponent(turn)].reset(start+5);
    out_end = child.get_all_successive_disc_captures_right(out_end,start+9);
  }
  
  // Down Right
  if((move::up11 & (opp_fields >> 6)).test(start)){
    child = *this;
    child.discs[turn] ^= ((1ul << start) | (1ul << (start+11)));
    child.discs[opponent(turn)].reset(start+6);
    child.kings[opponent(turn)].reset(start+6);
    out_end = child.get_all_successive_disc_captures_right(out_end,start+11);
  }
  
  if(out_begin == out_end){
    *out_end = *this;
    out_end++;
  }
  
  return out_end;
}


board* board::get_all_children_no_capture(board* out_end) const
{
  
  const std::bitset<50> empty_fields = get_empty_fields();
  std::bitset<50> inspected;
  
  if(turn==BLACK){
    
    // test up4
    inspected = discs[BLACK] & move::up4 & (empty_fields >> 4);
    while(inspected.any()){
      int index = find_first_set_64((inspected).to_ulong()) - 1;
      assert(index != -1);
      *out_end = *this;
      out_end->discs[BLACK] ^= (0x11 << index);
      out_end++;
      inspected.reset(index);
    }
    
    // test up5
    inspected = discs[BLACK] & move::up5 & (empty_fields >> 5);
    while(inspected.any()){
      int index = find_first_set_64((inspected).to_ulong()) - 1;
      assert(index != -1);
      *out_end = *this;
      out_end->discs[BLACK] ^= (0x21 << index);
      out_end++;
      inspected.reset(index);
    }

    // test up6
    inspected = discs[BLACK] & move::up6 & (empty_fields >> 6);
    while(inspected.any()){
      int index = find_first_set_64((inspected).to_ulong()) - 1;
      assert(index != -1);
      *out_end = *this;
      out_end->discs[BLACK] ^= (0x41 << index);
      out_end++;
      inspected.reset(index);
    }
    
  }
  else{
    // turn == WHITE
    
    // test down4
    inspected = discs[WHITE] & move::down4 & (empty_fields << 4);
    while(inspected.any()){
      int index = find_first_set_64((inspected).to_ulong()) - 1;
      assert(index != -1);
      *out_end = *this;
      out_end->discs[WHITE] ^= ((1ul << index) | (1ul << (index-4)));
      out_end++;
      inspected.reset(index);
    }
    
    // test down5
    inspected = discs[WHITE] & move::down5 & (empty_fields << 5);
    while(inspected.any()){
      int index = find_first_set_64((inspected).to_ulong()) - 1;
      assert(index != -1);
      *out_end = *this;
      out_end->discs[WHITE] ^= ((1ul << index) | (1ul << (index-5)));
      out_end++;
      inspected.reset(index);
    }
    
    // test down6
    inspected = discs[WHITE] & move::down6 & (empty_fields << 6);
    while(inspected.any()){
      int index = find_first_set_64((inspected).to_ulong()) - 1;
      assert(index != -1);
      *out_end = *this;
      out_end->discs[WHITE] ^= ((1ul << index) | (1ul << (index-6)));
      out_end++;
      inspected.reset(index);
    }
  }
  
  // test king moves
  inspected = kings[turn];
  while(inspected.any()){
    int index = find_first_set_64((inspected).to_ulong()) - 1;
    assert(index != -1);
    
    for(int d=0;d<4;d++){
      for(int i=0;i<move::king_dist_max[d][index];i++){
         int test_index = index + move::king_dist_diff[move::is_left.test(index) ? 1 : 0][d][i];
         if(!empty_fields.test(test_index)){
           break;
         }
         *out_end = *this;
         out_end->kings[turn] ^= ((1ul << index) | (1ul << test_index));
         out_end++;
      }
    }
    
    inspected.reset(index);
  }

  return out_end;
}
