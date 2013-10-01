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
  board* start_out = out;
  
  const std::bitset<50> empty_fields = get_empty_fields();
  std::bitset<50> inspected;
  
  if(turn==BLACK){
    
    // test up4
    inspected = discs[BLACK] & move::up4 & (empty_fields >> 4);
    while(inspected.any()){
      int index = find_first_set_64((inspected).to_ulong()) - 1;
      assert(index != -1);
      *out = *this;
      out->discs[BLACK] ^= (0x11 << index);
      out++;
      inspected.reset(index);
    }
    
    // test up5
    inspected = discs[BLACK] & move::up5 & (empty_fields >> 5);
    while(inspected.any()){
      int index = find_first_set_64((inspected).to_ulong()) - 1;
      assert(index != -1);
      *out = *this;
      out->discs[BLACK] ^= (0x21 << index);
      out++;
      inspected.reset(index);
    }

    // test up6
    inspected = discs[BLACK] & move::up6 & (empty_fields >> 6);
    while(inspected.any()){
      int index = find_first_set_64((inspected).to_ulong()) - 1;
      assert(index != -1);
      *out = *this;
      out->discs[BLACK] ^= (0x41 << index);
      out++;
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
      *out = *this;
      out->discs[WHITE] ^= ((1ul << index) | (1ul << (index-4)));
      out++;
      inspected.reset(index);
    }
    
    // test down5
    inspected = discs[WHITE] & move::down5 & (empty_fields << 5);
    while(inspected.any()){
      int index = find_first_set_64((inspected).to_ulong()) - 1;
      assert(index != -1);
      *out = *this;
      out->discs[WHITE] ^= ((1ul << index) | (1ul << (index-5)));
      out++;
      inspected.reset(index);
    }
    
    // test down6
    inspected = discs[WHITE] & move::down6 & (empty_fields << 6);
    while(inspected.any()){
      int index = find_first_set_64((inspected).to_ulong()) - 1;
      assert(index != -1);
      *out = *this;
      out->discs[WHITE] ^= ((1ul << index) | (1ul << (index-6)));
      out++;
      inspected.reset(index);
    }
  }
  
  *move_count = (out-start_out);
}
