#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>

#include "game.h"
#include "player.h"
#include "board.h"

Player::Player(std::string name, bool is_white){
  this-> name = name;
  this-> is_white = is_white;
};

std::vector<Piece*>& Player::get_pieces(){
  return pieces;
};

bool Player::get_color(){
  return is_white;
}

std::string Player::get_name(){
  return name;
}

void Player::start_pieces(Board& b){
  /*Can only receive one board in the initial position and, taking advantage
  of the location of the pieces, you store them according to color in order of
  value*/
  auto& aux_b = b.get_board();
  int i = is_white? 0:7;
  int m = is_white? 1:-1;
  pieces.push_back(aux_b[i][4]);
  pieces.push_back(aux_b[i][3]);
  pieces.push_back(aux_b[i][0]);
  pieces.push_back(aux_b[i][7]);
  pieces.push_back(aux_b[i][1]);
  pieces.push_back(aux_b[i][6]);
  pieces.push_back(aux_b[i][2]);
  pieces.push_back(aux_b[i][5]);
  for(int j=0; j<8; j++){
    pieces.push_back(aux_b[i+m][j]);
  }
};

//---------------------------- RealUser ------------------------------


void RealUser::paw_promotion(Piece* p){

}

std::array<std::pair<int, int>, 2> RealUser::play_turn(){
  return {};
}