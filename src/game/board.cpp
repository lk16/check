#include "board.hpp"

bool board::is_valid_move(int from,int to) const
{ 
  // if the square is not empty, it cannot be a valid move
  if(discs[turn].test(from) && !(discs[BLACK] | discs[WHITE]).test(to) 
  ){
    if(turn==WHITE){
      from = 50 - from;
      to = 50 - to;
    }
    int diff = to - from;
    switch(diff){
      case 4:
      case 5:
      case 6:
        return move::walk_possible[diff-4].test(from);
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
  *move_count = 0;
  (void)out;
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
      if((x%2==0) ^ (y%2==0)){
        std::cout << "  ";
        continue;
      }
      
      if(discs[BLACK].test(index)){
          std::cout << "\033[31;1m";
          std::cout << (is_king.test(index) ? '@' : 'x');
          std::cout << "\033[0m ";
      }
      else if(discs[WHITE].test(index)){
        std::cout << "\033[34;1m";
        std::cout << (is_king.test(index) ? '@' : 'x');
        std::cout << "\033[0m ";
      }
      else{
        std::cout << "  ";
      }
    }
    std::cout << "|\n";
  }
  
  /* bottom line */
  std::cout << "+---------------------+\n";
}