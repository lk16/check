#include "move.hpp"

int move::walk[3];
int move::capture[4];

std::bitset<50> move::walk_possible[3];
std::bitset<50> move::capture_possible[4];