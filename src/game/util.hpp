#ifndef CHECK_UTIL_HPP
#define CHECK_UTIL_HPP

#include <bitset>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>


#define LOCATION __FILE__ << ':' << __LINE__ << '\t'

#define BIT_SHIFT(var,shift) (((shift)>0) ? ((var) << (shift)) : ((var) >> (-(shift))))


#ifndef NDEBUG

  #define SHOW_VAR(a) std::cout << LOCATION << #a << " = " << (a) << std::endl 
  #define SHOW_VAR2(a,b)     SHOW_VAR(a);      SHOW_VAR(b)
  #define SHOW_VAR3(a,b,c)   SHOW_VAR2(a,b);   SHOW_VAR(c)
  #define SHOW_VAR4(a,b,c,d) SHOW_VAR3(a,b,c); SHOW_VAR(d)
  #define PING std::cout << LOCATION << "PING!\n"
  #define CONTAINS_BUG std::cout << LOCATION << "Do not use this function, it contains bugs!\n"
  #define NOT_IMPLEMENTED std::cout << LOCATION << "This is not implemented yet!\n" 
  #define CRASH std::cout << LOCATION << "I'm crashing!\n"; abort()

#else

  #define SHOW_VAR(a)
  #define SHOW_VAR2(a,b)
  #define SHOW_VAR3(a,b,c)
  #define SHOW_VAR4(a,b,c,d)
  #define PING
  #define CONTAINS_BUG
  #define NOT_IMPLEMENTED
  #define CRASH
  
#endif

/// subdirectory where images are stored
#define IMAGE_PATH std::string("./images/")

/// subdirectory where xml files containing ui are stored
#define UI_PATH std::string("./xml/")

/// perfect score factor
#define EXACT_SCORE_FACTOR (1000)

/// heighest possible heuristic value
#define MAX_HEURISTIC (EXACT_SCORE_FACTOR * 64)

/// lowest possible heuristic value
#define MIN_HEURISTIC (-1 * MAX_HEURISTIC)

enum color{
  BLACK = 0,
  WHITE = 1,
  EMPTY = 2
};

inline color opponent(color c){
  assert(c==WHITE || c==BLACK);
  return ((c==BLACK) ? WHITE : BLACK);
}

template<class T>
inline T min(T x,T y){
  return ((x<y) ? x : y);
}

template<class T>
inline T max(T x,T y){
  return ((x>y) ? x : y);
}


template<class T>
inline T abs(T x){
  return ((x<0) ? x : (-x));
}

template<class T>
inline std::string tostr(T x){
  std::stringstream buff;
  buff << x;
  return buff.str();
}

template<class T>
inline T fromstr(std::string x){
  std::stringstream buff(x);
  T temp;
  buff >> temp;
  return temp;
}

inline std::string big_number(long long x){
  std::stringstream ss;
  if(x>10000000l){
    x /= 1000000l;
    ss << x << 'M';
  }
  else if(x>1000l){
    x /= 1000l;
    ss << x << 'K';
  }
  else{
    ss << x;
  }
  
  return ss.str();
}

inline void show_bitset(const std::bitset<50>& bs){
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
      
      std::cout << (bs.test(index) ? "@ " : "  ");
      index++;
    }
    std::cout << "|\n";
  }
  
  /* bottom line */
  std::cout << "+---------------------+\n";
}

// returns 0 if ul==0ul, returns 1 + least significant bit otherwise
inline int find_first_set_64(unsigned long ul){
  int res = __builtin_ffs(ul & 0x00000000FFFFFFFF);
  if(res!=0){
    return res;
  }
  res = __builtin_ffs(ul >> 32);
  if(res!=0){
    return 32 + res;
  }
  return 0;
}


#endif
