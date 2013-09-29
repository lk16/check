#include "board.hpp"

bool board::is_valid_move(int from,int to) const
{ 
  // if the square is not empty, it cannot be a valid move
  if(discs[turn].test(from) && !(discs[BLACK] | discs[WHITE]).test(to) 
  ){
    if(turn==WHITE){
      
      
      
    }
  }
  
  
  
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
          std::cout << "\033[31;1m";
          std::cout << (is_king.test(index) ? '@' : 'o');
          std::cout << "\033[0m ";
      }
      else if(discs[WHITE].test(index)){
        std::cout << "\033[34;1m";
        std::cout << (is_king.test(index) ? '@' : 'o');
        std::cout << "\033[0m ";
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
  NOT_IMPLEMENTED;
  *max_streak = *move_count = 0;
}

