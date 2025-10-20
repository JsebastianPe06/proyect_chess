/*
This .cpp contain the board class and its methods for create a board in the
initial position, validate and save the movements, and keep states of the game 
*/

#include <iostream>
#include <string>
#include <vector>

#include "board.h"
#include "pieces.h"


//--------------- Board -------------------
Board::Board(){
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      board[i][j] = nullptr;
    };
  };
};

Board::~Board(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            delete board[i][j];
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Board& p){
  for (int i = 7; i >= 0; i--){
    for (int j = 0; j < 8; j++){
      if (p.board[i][j] == nullptr){
        os << ".  "; 
      }
      else {
        os << *p.board[i][j] << " ";
      }
    }
    os << "\n";
  }
  return os;
};

/*The following functions are those that generate the initial position of the
board*/
void Board::starting_pawn(){
  for(int i=0; i<8; i++){
    board[1][i] = new Pawn(1, 1, i);
    board[6][i] = new Pawn(0, 6, i);
  }
};

void Board::starting_rook(){
  board[0][0] = new Rook(1, 0, 0);
  board[0][7] = new Rook(1, 0, 7);
  board[7][0] = new Rook(0, 7, 0);
  board[7][7] = new Rook(0, 7, 7);
};

void Board::starting_knight(){
  board[0][1] = new Knight(1, 0, 1);
  board[0][6] = new Knight(1, 0, 6);
  board[7][1] = new Knight(0, 7, 1);
  board[7][6] = new Knight(0, 7, 6);
};

void Board::starting_bishop(){
  board[0][2] = new Bishop(1, 0, 2);
  board[0][5] = new Bishop(1, 0, 5);
  board[7][2] = new Bishop(0, 7, 2);
  board[7][5] = new Bishop(0, 7, 5);
};

void Board::starting_queen(){
  board[0][3] = new Queen(1, 0, 3);
  board[7][3] = new Queen(0, 7, 3);
};

void Board::starting_king(){
  board[0][4] = new King(1, 0, 4);
  board[7][4] = new King(0, 7, 4);
};

void Board::starting_position(){
  Board::starting_king();
  Board::starting_pawn();
  Board::starting_rook();
  Board::starting_knight();
  Board::starting_bishop();
  Board::starting_queen();
};
//---------------------------------------------------------------------------
//----------------------------- Analyze METHODS --------------------------------

bool Board::attack_row(const std::pair<int,int> square, Piece* attacked){
  /*This method determines whether a piece is being attacked by a rook or queen
  based on the rank of a square*/
  int f = square.first;
  int c = square.second;
  bool validation = false;
  bool is_attacked = false;
  int step = (attacked->get_column()>c)? 1:-1;
  int i = c+step;
  // Search for the attacked piece in the same row
  while(!validation && i>=0 && i<8){
    Piece* p = board[f][i];
    if(p!=nullptr){
      if(p==attacked) validation = true;
      else break;
    }
    i += step;
  }
  if(!validation) return false;
  // Search in the opposite direction for an enemy sliding piece
  i = c;
  while(!is_attacked && i>= 0 && i<8){
    Piece* p = board[f][i];
    if (p != nullptr) {
      if (p->get_color() != attacked->get_color()) {
        if (p->is_moves_rook) // can move like a rook (rook/queen)
          is_attacked = p->is_moves_rook; // ensure only rook/queen logic applies
      }
      break;
    }
    i -= step;
  }
  return is_attacked;
};

bool Board::attack_column(const std::pair<int,int> square, Piece* attacked){
  /*This method determines whether a piece is being attacked by a rook or queen
  based on the column of a square*/
  int f = square.first;
  int c = square.second;
  bool validation = false;
  bool is_attacked = false;
  int step = (attacked->get_row()>f)? 1:-1;
  int i = f+step;
  // Search for the attacked piece in the same column
  while(!validation && i>=0 && i<8){
    Piece* p = board[i][c];
    if(p!=nullptr){
      if(p==attacked) validation = true;
      else break;
    }
    i += step;
  }
  if(!validation) return false;
  // Search in the opposite direction for an enemy sliding piece
  i = f;
  while(!is_attacked && i>= 0 && i<8){
    Piece* p = board[i][c];
    if(p!=nullptr) {
      if (p->get_color()!=attacked->get_color()){
        if(p->is_moves_rook) // rook or queen type
          is_attacked = true;
      }
      break;
    }
    i -= step;
  }
  return is_attacked;
};

bool Board::attack_major_diagonal(const std::pair<int,int> square, Piece* attacked){
  /*This method determines whether a piece is being attacked by a bishop or
  queen based on the major diagonal of a square.*/
  int f = square.first;
  int c = square.second;
  bool validation = false;
  bool is_attacked = false;
  int step_f = (attacked->get_row()>f)? 1:-1;
  int step_c = (attacked->get_column()>c)? 1:-1;
  int i = f + step_f;
  int j = c + step_c;
  // Search for the attacked piece in the same diagonal
  while (!validation && i>=0 && i<8 && j>=0 && j<8){
    Piece* p = board[i][j];
    if(p!=nullptr){
      if(p==attacked) validation = true;
      else break;
    }
    i += step_f;
    j += step_c;
  }
  if(!validation) return false;
  // Search in the opposite direction for an enemy sliding piece
  i = f;
  j = c;
  while(!is_attacked && i>=0 && i<8 && j>=0 && j<8){
    Piece* p = board[i][j];
    if(p != nullptr){
      if(p->get_color() != attacked->get_color()){
        if(p->is_moves_bishop) // bishop or queen type
          is_attacked = true;
      }
      break;
    }
    i -= step_f;
    j -= step_c;
  }
  return is_attacked;
}

bool Board::attack_minor_diagonal(const std::pair<int,int> square, Piece* attacked){
  /*This method determines whether a piece is being attacked by a bishop or
  queen based on the minor diagonal of a square.*/
  int f = square.first;
  int c = square.second;
  bool validation = false;
  bool is_attacked = false;
  int step_f = (attacked->get_row()>f)? 1:-1;
  int step_c = (attacked->get_column()>c)? -1:1;
  int i = f + step_f;
  int j = c + step_c;
  // Search for the attacked piece in the same diagonal
  while(!validation && i >= 0 && i < 8 && j >= 0 && j < 8){
    Piece* p = board[i][j];
    if(p != nullptr){
      if(p==attacked) validation = true;
      else break;
    }
    i += step_f;
    j += step_c;
  }
  if(!validation) return false;
  // Search in the opposite direction for an enemy sliding piece
  i = f;
  j = c;
  while(!is_attacked && i>=0 && i<8 && j>=0 && j<8){
    Piece* p = board[i][j];
    if(p!=nullptr){
      if(p->get_color()!=attacked->get_color()){
        if(p->is_moves_bishop) // bishop or queen type
          is_attacked = true;
      }
      break;
    }
    i -= step_f;
    j -= step_c;
  }
  return is_attacked;
};

bool Board::is_sliding_attack(const std::pair<int,int> square, Piece* attacked){
  /*This method shows if a piece is being attacked by another given a position,
  it works with sliding pieces (rook, queen, bishop) looking from a given
  square if there is an attack by row, column or diagonal that passes through
  the square.*/
  //attribute to knows whether is neccesary the diagonal
  int d1 = square.first-attacked->get_row(); 
  int d2 = square.second-attacked->get_column();
  //--
  if(square.first==attacked->get_row()){
    return attack_row(square, attacked);
  }
  else if(square.second==attacked->get_column()){
    return attack_column(square, attacked);
  }
  else if(d1==-d2){
    return attack_major_diagonal(square, attacked);
  }
  else if(d1==+d2){
    return attack_minor_diagonal(square, attacked);
  }
  return 0;
};