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
  
  *move_count = 0;
  (void)out;
  
  std::bitset<50> moveable_discs;
  std::bitset<50> capturing_discs;
  std::bitset<50> any_disc = discs[BLACK] | discs[WHITE];
  std::bitset<50> my_kings;
  if(turn==WHITE){
    my_kings = discs[WHITE] & is_king;
    // do i have a king?
    if(my_kings.any()){
      // yes, i have a king!
      
      NOT_IMPLEMENTED;
      CRASH;
      
    }
      
      
    for(int i=0;i<4;i++){
      
      
      
      // for all discs of my color
      // is capture in this direction possible, capture_possible[i]
      // is there an empty field at my index + move::capture[i]
      // is there a disc to capture?
    
    }
      
      
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