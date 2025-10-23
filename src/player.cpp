#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <random>

#include "game.h"
#include "player.h"
#include "board.h"
#include "interface.h"

Player::Player(std::string name, bool is_white){
  this-> name = name;
  this-> is_white = is_white;
};

Player::~Player() = default;


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

void RealUser::paw_promotion(Piece* p, Board& b){
  /*When a pawn reaches its maximum rank, it chooses which piece to bring to
  the board for the pawn*/
  int option;
  if(p->get_name() != "Pawn") return;
  while(true){
    std::cout << "================================\n" << std::endl;
    std::cout << "           Promotion               \n" << std::endl;
    std::cout << "================================\n" << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << "1. In Queen\n" << std::endl;
    std::cout << "2. In Bishop\n" << std::endl;
    std::cout << "3. In Rook\n" << std::endl;
    std::cout << "4. In knight\n" << std::endl;
    std::cout << "Enter an option (1-4): ";
    std::cin >> option;
    if(option<1 || option>4){
      std::cout << "Error. Value out of range\n" << std::endl;
    }
    else break;
  }
  bool color = p->get_color();
  int row = p->get_row();
  int col = p->get_column();
  Piece* new_p = nullptr;
  switch(option){
    case 1:
      new_p = new Queen(color, row, col);
      break;
    case 2:
      new_p = new Bishop(color, row, col);
      break;
    case 3:
      new_p = new Rook(color, row, col);
      break;
    case 4:
      new_p = new Knight(color, row, col);
      break;
  }
  auto& board = b.get_board();
  delete board[row][col];
  board[row][col] = new_p;
  for (size_t i = 0; i<pieces.size(); ++i){
    if(pieces[i]==p){
      pieces[i] = new_p;   
      break;
    }
  }
};

std::array<std::pair<int,int>,2> RealUser::play_turn(const Board& board){
  while(true){
    /*The user chooses a piece and a move*/
    std::cout << "\nCurrent Board:\n" << std::endl;
    std::cout << board << "\n" << std::endl;
    // Show pieces with possible moves
    int choice = 0;
    int mov = 0;
    bool val_move = false;
    int max = pieces.size();
    std::string colr = get_color()? "White":"Black";
    while(true){
      std::cout << "Your pieces " << colr <<" with moves:\n" << std::endl;
      for(int i=0; i<max; i++){
        int aux_f = pieces[i]->get_row();
        int aux_c = pieces[i]->get_column();
        std::cout << "[" << i+1 << "]" << pieces[i]->get_name() << "(" << aux_f << "," << aux_c << ")" << std::endl;
      }
      //cooses piece
      std::cout << "Select a piece to move by number: ";
      std::cin >> choice;
      if(choice>0 && choice<=max){
        if(pieces[choice-1]->get_moves().empty()){
          std::cout << "This piece has no possible moves\n" << std::endl;
        }
        else{
          Piece* p = pieces[choice-1];
          std::vector<std::pair<int, int>> moves_p = p->get_moves(); 
          int max_mo = moves_p.size();
          while(true){
            for(int i=0; i<max_mo; i++){
              int aux_pf = moves_p[i].first;
              int aux_pc = moves_p[i].second;
              std::cout << "[" << i+1 << "]" << "(" << aux_pf << "," << aux_pc << ")" << std::endl;
            }
            //choses move
            std::cout << "Select a move to use by number (0 to exit): ";
            std::cin >> mov;
            if(mov==0) break;
            if(mov<0 || mov>max_mo){
              std::cout << "Error. Value out of range\n" << std::endl;
            }
            else{
              return {{p->get_actual_pos(),moves_p[mov-1]}};
            }
          } 
        }
      }
      else{
          std::cout << "Error. Value out of range\n" << std::endl;
      }
    }
  }
};


//---------------------------- RandomBot ------------------------------

RandomBot::RandomBot(bool is_white)
  :Player("RandomBot", is_white), gen(std::random_device{}()){
};

int RandomBot::random_int(int a, int b) {
    std::uniform_int_distribution<int> dist(a, b);
    return dist(gen);
}

void RandomBot::paw_promotion(Piece* p, Board& b){
  int cas = random_int(0, pieces.size()-1);
  bool color = p->get_color();
  int row = p->get_row();
  int col = p->get_column();
  Piece* new_p = nullptr;
  switch(cas){
    case 1:
      new_p = new Queen(color, row, col);
      break;
    case 2:
      new_p = new Bishop(color, row, col);
      break;
    case 3:
      new_p = new Rook(color, row, col);
      break;
    case 4:
      new_p = new Knight(color, row, col);
      break;
  }
  auto& board = b.get_board();
  delete board[row][col];
  board[row][col] = new_p;
  for (size_t i = 0; i<pieces.size(); ++i){
    if(pieces[i]==p){
      pieces[i] = new_p;   
      break;
    }
  }
}

std::array<std::pair<int, int>, 2> RandomBot::play_turn(const Board& board){
  int pos_p = random_int(0, pieces.size()-1);
  while(pieces[pos_p]->get_moves().size()==0){
    pos_p = random_int(0, pieces.size()-1);
  }
  int pos_m = random_int(0, pieces[pos_p]->get_moves().size()-1);
  std::pair<int, int> new_pos = pieces[pos_p]->get_moves()[pos_m];
  std::cout << "The RandomBot has moved the piece " << pieces[pos_p]->get_name()
  << " to (" << new_pos.first << "," << new_pos.second << ")" << std::endl;
  return {pieces[pos_p]->get_actual_pos(), new_pos};
};