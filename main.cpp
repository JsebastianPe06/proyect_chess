#include <iostream>
#include "include/pieces.h"
#include "include/board.h"

int main(){
  std::ios::sync_with_stdio(false);
  std::setvbuf(stdout, nullptr, _IONBF, 0);

  Board a;
  a.starting_position();
  Piece& f = *a.get_board()[0][0];
  Piece& b = *a.get_board()[7][2];
  int pos1[2] = {4,5};
  a.move_piece(a.get_board()[0][0], pos1);
  int pos2[2] = {3,3};
  a.move_piece(a.get_board()[7][2], pos2);
  std::cout << a << std::endl;
  std::cout << a.is_sliding_attack(f.get_actual_pos(),a.get_board()[6][5]) <<std::endl;
  std::cout << a.is_sliding_attack(b.get_actual_pos(),a.get_board()[1][5]) <<std::endl;
  std::cout << a.is_sliding_attack(f.get_actual_pos(),a.get_board()[1][5]) <<std::endl;
  std::cout << a.is_sliding_attack(f.get_actual_pos(),a.get_board()[7][5]) <<std::endl;
  a.move_piece(a.get_board()[3][3], pos1);
  std::cout << a << std::endl;
  std::cout << a.is_sliding_attack(b.get_actual_pos(),a.get_board()[1][5]) <<std::endl;
  return 0;
};