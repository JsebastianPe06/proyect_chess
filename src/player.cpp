#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <cstdlib>
#include <ctime>

#include "game.h"
#include "player.h"
#include "board.h"
#include "interface.h"

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

RealUser::RealUser(std::string name, bool is_white)
  :Player(name, is_white){}

void RealUser::paw_promotion(Piece* p) {
  // This method can be later adapted to a GUI popup
  ;
}

std::array<std::pair<int,int>,2> RealUser::play_turn(const Board& board, const std::vector<Piece*>& pieces) {
  std::cout << "\nCurrent Board:\n";
  std::cout << board << "\n";
  // Show pieces with possible moves
  std::cout << "Your pieces with possible moves:\n";
  int idx = 1;
  std::vector<std::pair<int,int>> piece_positions;
  for (auto* p : pieces) {
    if (!p->get_moves().empty()) {
      std::cout << idx << ". " << p->get_name() << " at (" << p->get_row() << "," << p->get_column() << ")\n";
      piece_positions.push_back(p->get_actual_pos());
      idx++;
    }
  }
  int choice;
  std::cout << "Select a piece to move by number: ";
  std::cin >> choice;
  if(choice < 1 || choice > (int)piece_positions.size()) 
    return {std::pair<int,int>{-1,-1}, std::pair<int,int>{-1,-1} };
  std::pair<int,int> from = piece_positions[choice-1];
  //Show possible moves for the selected piece
  Piece* selected_piece = nullptr;
  for(auto* p : pieces) {
    if(p->get_actual_pos() == from){
      selected_piece = p;
      break;
    }
  }
  std::cout << "Possible moves:\n";
  idx = 1;
  for(auto mv : selected_piece->get_moves()){
    std::cout << idx << ". (" << mv.first << "," << mv.second << ")\n";
    idx++;
  }
  std::cout << "Select destination by number: ";
  int move_choice;
  std::cin >> move_choice;
  if(move_choice < 1 || move_choice > (int)selected_piece->get_moves().size())
    return {std::pair<int,int>{-1,-1}, std::pair<int,int>{-1,-1}};
  std::pair<int,int> to = selected_piece->get_moves()[move_choice-1];
  return {from, to};
}

//---------------------------- RandomBot ------------------------------

RandomBot::RandomBot(bool is_white)
  : Player("Bot", is_white) {
  std::srand(std::time(nullptr));
}

void RandomBot::paw_promotion(Piece* p) {
  // Auto promote to queen
  std::cout << "Bot pawn promoted automatically.\n";
}

std::array<std::pair<int,int>,2> play_turn(Board& board, const std::vector<Piece*>& pieces){
  std::vector<std::pair<Piece*, std::pair<int,int>>> all_moves;
  for (auto* p : pieces) {
    p->possible_moves(board);
    for (auto& m : p->get_moves())
      all_moves.push_back({p, m});
  }
  if (all_moves.empty())
    return { std::make_pair(-1,-1), std::make_pair(-1,-1) };
  int idx = std::rand() % all_moves.size();
  return { all_moves[idx].first->get_actual_pos(), all_moves[idx].second };
}

void paw_promotion(Piece* p){
  std::cout << "Bot pawn promoted automatically to Queen.\n";
};