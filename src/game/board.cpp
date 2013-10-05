#include "board.hpp"

bool board::is_valid_move(int from,int to) const
{ 
  
  /// WARNING: NOT TESTED YET
  
  int from_type = -1; // 0 -> disc, 1 -> king
  if(discs[turn].test(from)){
    from_type = 0;
  }
  if(kings[turn].test(from)){
    from_type = 1;
  }
  if(from_type == -1){
    return false;
  }
  if(!get_empty_fields().test(to)){
    return false;
  }
  
  // test if there is any overlap between
  // - get_children() of *this 
  // - get_children() of *this after doing the move of 'from' to 'to'
  
  board children_before[100];
  board children_after[100];
  board after;
  int before_move_count,after_move_count;
  
  
  get_children(children_before,&before_move_count);
  do_move(from,to,&after);
  after.get_children(children_after,&after_move_count);
  
  for(int a=0;a<after_move_count;a++){
    for(int b=0;b<before_move_count;b++){
      if(children_after[a] == children_before[b]){
        return true;
      }
    }
  }
  
  return false;
}

void board::do_move(int from,int to, board* out) const
{
  
  /// WARNING: NOT TESTED YET
  
  *out = *this;
  
  bool is_left = move::is_left.test(from);  
  color opp = opponent(turn);
  
  
  if(discs[turn].test(from)){
    switch(to-from){
      case -11:
        assert(move::down11.test(from));
        out->discs[opp].reset(from + (is_left ? -6 : -5));
        out->kings[opp].reset(from + (is_left ? -6 : -5));
        break;
      case -9:
        assert(move::down9.test(from));
        out->discs[opp].reset(from + (is_left ? -4 : -5));
        out->kings[opp].reset(from + (is_left ? -4 : -5));
        break;
      case 9:
        assert(move::up9.test(from));
        out->discs[opp].reset(from + (is_left ? 5 : 4));
        out->kings[opp].reset(from + (is_left ? 5 : 4));
        break;
      case 11:
        assert(move::up11.test(from));
        out->discs[opp].reset(from + (is_left ? 6 : 5));
        out->kings[opp].reset(from + (is_left ? 6 : 5));
        break;
      case -6:
      case -5:
      case -4:
      case 4:
      case 5:
      case 6:
        break;
      default:
        assert(0);
        break;        
    }
    out->discs[turn] ^= ((1ul << from) | (1ul << to));
  }
  else{
    assert(kings[turn].test(from));
    int dir = -1;
    for(int d=0;d<4;d++){
      for(int i=0;i<9;i++){
        if(from + move::king_dist_diff[is_left][d][i] == to){
          dir = d;
          break;
        }
      }
      if(d!=-1){
        break;
      }
    }
    
    for(int i=0;i<move::king_dist_max[dir][from];i++){
      int tested = from + move::king_dist_diff[is_left][dir][i];
      if(tested == to){
        break;
      }
      out->discs[opp].reset(tested);
      out->kings[opp].reset(tested);
    }
    
    
    out->kings[turn] ^= ((1ul << from) | (1ul << to));
  }
  
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
  
  for(board* out_iter=out_begin;out_iter!=out_end;out_iter++){
    // disc to king promotion
    std::bitset<50> promoted;
    
    promoted = (out_iter->discs[WHITE] & move::border_top);
    out_iter->discs[WHITE] &= (~promoted);
    out_iter->kings[WHITE] |= (promoted);
    
    promoted = (out_iter->discs[BLACK] & move::border_bottom);
    out_iter->discs[BLACK] &= (~promoted);
    out_iter->kings[BLACK] |= (promoted);
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

board* board::get_max_king_capture_streak(board* out_begin) const
{
  board* out_end = out_begin;
  color opp = opponent(turn);
  
  std::bitset<50> inspected;
  
  inspected = kings[turn];
  while(inspected.any()){
    int index = find_first_set_64((inspected).to_ulong()) - 1;
    assert(index!=-1);
    out_end = get_all_successive_king_captures(out_end,index);
    inspected.reset(index);
  }
  
  board* fill_iter = out_begin;
  int min_num_opp_fields = 50;
    
  for(board* out_iter=out_begin;out_iter!=out_end;out_iter++){ 
    int num_opp_fields = (out_iter->discs[opp] | out_iter->kings[opp]).count();
    if(num_opp_fields < min_num_opp_fields){
      min_num_opp_fields = num_opp_fields;
      fill_iter = out_begin;
    }
    if(num_opp_fields == min_num_opp_fields){
      *fill_iter = *out_iter;
      fill_iter++;
    }
  }
    
  return fill_iter;
}

board* board::get_all_successive_king_captures(board* out_begin, int start) const
{
  assert(kings[turn].test(start));
  
  board* out_end = out_begin;
  
  std::bitset<50> my_fields  = discs[turn] | kings[turn];
  std::bitset<50> opp_fields = discs[opponent(turn)] | kings[opponent(turn)];
  
  
  bool is_left = move::is_left.test(start);
  
  for(int dir=0;dir<4;dir++){
    
    // make sure we dont capture twice per direction per recursive call
    int capturable_field = -1;
    
    
    int step_size = 0;
    while(step_size<move::king_dist_max[dir][start]){
      const int tested = start + move::king_dist_diff[is_left][dir][step_size];
      
      if(my_fields.test(tested)){
        // can not proceed this direction
        break;
      }
      else if(opp_fields.test(tested)){
        if(capturable_field != -1){ 
          // already found capturable field this dircection for this recursive call
          break;
        }
        else{ 
          capturable_field = tested;
        }
      }
      else if(capturable_field != -1){
        assert(get_empty_fields().test(tested));
        board child = *this;
        child.kings[turn] ^= ((1ul << start) | (1ul << tested));
        child.discs[opponent(turn)].reset(capturable_field);
        child.kings[opponent(turn)].reset(capturable_field);
        out_end = child.get_all_successive_king_captures(out_end,tested);
        
        // TODO dont add child if above recursive calls added any 
        *out_end = child;
        out_end++;
      }
      
      
      // try walking one step further in same direction
      step_size++;
    }
  }
  return out_end;
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
  
  board* fill_iter = out_begin;
  int min_num_opp_fields = 50;
  
  for(board* out_iter=out_begin;out_iter!=out_end;out_iter++){ 
    int num_opp_fields = (out_iter->discs[opp] | out_iter->kings[opp]).count();
    if(num_opp_fields < min_num_opp_fields){
      min_num_opp_fields = num_opp_fields;
      fill_iter = out_begin;
    }
    if(num_opp_fields == min_num_opp_fields){
      *fill_iter = *out_iter;
      fill_iter++;
    }
  }
  
  return fill_iter;
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
