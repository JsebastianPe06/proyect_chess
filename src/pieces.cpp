#include <iostream>
#include <string>
#include <array>
#include <vector>

#include "pieces.h"
#include "board.h"

/*
This .cpp contains the Piece classes, with methods for calculate possible
movements and save states for determinate valid movements
*/

//----------Piece-------------
Piece::Piece(bool color, int f, int c, int value){
  this -> color = color;
  this -> f = f;
  this -> c = c;
  this -> value = value;
};

Piece::~Piece(){};

//Methods set an get of rows(f) and columns(c)
int Piece::get_row(){
  return f;
};
int Piece::get_column(){
  return c;
};
void Piece::set_row(int new_f){
  f = new_f;
};
void Piece::set_column(int new_c){
  c = new_c;
};
std::pair<int,int> Piece::get_actual_pos(){
  return {f, c};
};
void Piece::set_actual_pos(int new_pos[2]){
  /*receives an array of the form {row(f), column(c)} to update row and column
  of the piece */
  f = new_pos[0];
  c = new_pos[1];
};
//-----------------
bool Piece::get_color(){
  return color;
};
std::string Piece::get_name(){
  return name;
};
int Piece::get_value(){
  return value;
};

std::vector<std::pair<int, int>> Piece::get_moves(){
  return pos_moves;
}

void Piece::set_moves(std::vector<std::pair<int, int>> m){
  pos_moves = m;
}

void Piece::display(std::ostream& os) const{
    os << name[0] << (color? 'w':'b');
};
std::ostream& operator<<(std::ostream& os, const Piece& p){
  p.display(os);
  return os;
};

bool Piece::is_pinned(Board& b, Piece* p){
  /*Method that mean weather a piece is pinned for other, that is to say,
  whether the piece getted is doing attacked for other*/
  Piece* aux = b.get_board()[f][c];
  b.get_board()[f][c] = nullptr;
  bool is_pin = b.is_sliding_attack(get_actual_pos(), p);
  b.get_board()[f][c] = aux;
  return is_pin;
};


// ------------------------------ piece pawn ---------------------------------
Pawn::Pawn(bool color, int f, int c): Piece(color, f, c, 1){
  name = "Pawn";
  is_moves_bishop = 0;
  is_moves_rook = 0;
  is_first_move = 1;
};

  void Pawn::possible_moves(Board& b){
  /*Method that return the pawn's movement including possibles passant
  without included pawn promotion*/
  int dir = color? -1:1;
  std::vector<std::pair<int, int>> moves;
  auto& board = b.get_board();
  //advance one square
  if(board[f+dir][c]==nullptr){
    moves.push_back({f+dir,c});
    if(is_first_move && board[f+(2*dir)][c]==nullptr){
      moves.push_back({f+(2*dir),c});
    }
  }
  //capture
  if(c!=7){
    if(board[f+dir][c+1]!=nullptr) moves.push_back({f+dir, c+1});
  }
  if(c!=0){
    if(board[f+dir][c-1]!=nullptr) moves.push_back({f+dir, c-1});
  }
  pos_moves = moves;
};

bool Pawn::is_attacking(Piece* p){
  /*Given a piece, it returns if the pawn is attacking the piece, it also works
  with allied pieces to know if a piece or the pawn is defending the piece.*/
  std::pair<int, int> pos_p = p->get_actual_pos();
  pos_p.first -= (color? 1:-1);
  int m = pos_p.second - c;
  return (m==1 || m==-1);
};


//------------------------- piece rook ------------------------------------
Rook::Rook(bool color, int f, int c): Piece(color, f, c, 5){
  name = "Rook";
  is_moves_bishop = 0;
  is_moves_rook = 1;
};
const std::pair<int, int> Rook::dir[4] = {{1,0}, {0,-1}, {-1,0}, {0,1}};

void Rook::possible_moves(Board& b){
  /*Method that returns all possible rook moves (castling is a king move)*/
  std::vector<std::pair<int, int>> moves;
  auto& board = b.get_board();
  for(int i=0; i<4; i++){
    int dir_f = dir[i].first;
    int dir_c = dir[i].second;
    int aux_f = f+dir_f;
    int aux_c = c+dir_c;
    while(aux_f>=0 && aux_f<8 && aux_c>=0 && aux_c<8){
      if(board[aux_f][aux_c]==nullptr) moves.push_back({aux_f, aux_c});
      else if(board[aux_f][aux_c]->get_color()==color) break;
      else if(board[aux_f][aux_c]->get_color()!=color){
        moves.push_back({aux_f, aux_c});
        break;
      }
      aux_f += dir_f;
      aux_c += dir_c; 
    }
  }
  pos_moves = moves;
};

bool Rook::is_attacking(Piece* p){
  return 0;
};


//------------------------- piece kinght -----------------------------------
Knight::Knight(bool color, int f, int c): Piece(color, f, c, 3){
  name = "Knight";
  is_moves_bishop = 0;
  is_moves_rook = 0;
};
const std::pair<int, int> Knight::dir[8] = {{1,2}, {-1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2},
{-2,-1}, {-2,1}};

void Knight::possible_moves(Board& b){
  /*Method that returns all possible knight moves*/
  std::vector<std::pair<int, int>> moves;
  auto& board = b.get_board();
  for(int i=0; i<8; i++){
    int aux_f = f+dir[i].first;
    int aux_c = c+dir[i].second;
    if(aux_f>=0 && aux_f<8 && aux_c>=0 && aux_c<8){
      if(board[aux_f][aux_c]==nullptr) moves.push_back({aux_f,aux_c});
      else if(board[aux_f][aux_c]->get_color()!=color) moves.push_back({aux_f,aux_c});
    }
  }
  pos_moves = moves;
};

void Knight::display(std::ostream& os) const {
    os << 'N' << (color? 'w':'b');
}

bool Knight::is_attacking(Piece* p){
  /*Given a piece, it returns if the pawn is attacking the piece, it also works
  with allied pieces to know if a piece or the pawn is defending the piece.*/
  std::pair<int,int> pos_p = p->get_actual_pos();
  int df = std::abs(pos_p.first-f);
  int dc = std::abs(pos_p.second-c);
  return ((df==1 && dc==2) || (df==2 && dc==1));
}


//---------------------------- piece bishop --------------------------------
Bishop::Bishop(bool color, int f, int c): Piece(color, f, c, 3){
  name = "Bishop";
  is_moves_bishop = 1;
  is_moves_rook = 0;
};
const std::pair<int, int> Bishop::dir[4] = {{1,1}, {1,-1}, {-1,-1}, {-1,1}};

void Bishop::possible_moves(Board& b){
  /*Method that returns all possible bishop moves*/
  std::vector<std::pair<int, int>> moves;
  auto& board = b.get_board();
  for(int i=0; i<4; i++){
    int dir_f = dir[i].first;
    int dir_c = dir[i].second;
    int aux_f = f+dir_f;
    int aux_c = c+dir_c;
    while(aux_f>=0 && aux_f<8 && aux_c>=0 && aux_c<8){
      if(board[aux_f][aux_c] == nullptr) moves.push_back({aux_f, aux_c});
      else if(board[aux_f][aux_c]->get_color()==color) break;
      else{
        moves.push_back({aux_f, aux_c});
        break;
      }
      aux_f += dir_f;
      aux_c += dir_c;
    }
  }
  pos_moves = moves;
}

bool Bishop::is_attacking(Piece* p){
  return 0;
};


//------------------------------ piece queen -------------------------------
Queen::Queen(bool color, int f, int c): Piece(color, f, c, 10){
  name = "Queen";
  is_moves_bishop = 1;
  is_moves_rook = 1;
};
const std::pair<int, int> Queen::dir[8] = {{1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0},
{-1,1}, {0,1}};

void Queen::possible_moves(Board& b){
  /*Method that returns all possible queen moves*/
  std::vector<std::pair<int, int>> moves;
  auto& board = b.get_board();
  for(int i=0; i<8; i++){
    int dir_f = dir[i].first;
    int dir_c = dir[i].second;
    int aux_f = f+dir_f;
    int aux_c = c+dir_c;
    while(aux_f>=0 && aux_f<8 && aux_c>=0 && aux_c<8){
      if(board[aux_f][aux_c] == nullptr) moves.push_back({aux_f, aux_c});
      else if(board[aux_f][aux_c]->get_color() == color) break;
      else{
        moves.push_back({aux_f, aux_c});
        break;
      }
      aux_f += dir_f;
      aux_c += dir_c;
    }
  }
  pos_moves = moves;
}

bool Queen::is_attacking(Piece* p){
  return 0;
};


//----------------------------- piece king ---------------------------------
King::King(bool color, int f, int c): Piece(color, f, c, 1000){
  name = "King";
  is_moves_bishop = 0;
  is_moves_rook = 0;
};
const std::pair<int, int> King::dir[8] = {{1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0},
{-1,1}, {0,1}};

void King::possible_moves(Board& b){
  /*Method that returns all possible King moves*/
  std::vector<std::pair<int, int>> moves;
  auto& board = b.get_board();
  for(int i=0; i<8; i++){
    int aux_f = f+dir[i].first;
    int aux_c = c+dir[i].second;
    if(aux_f>=0 && aux_f<8 && aux_c>=0 && aux_c<8){
      if(board[aux_f][aux_c]==nullptr) moves.push_back({aux_f,aux_c});
      else if(board[aux_f][aux_c]->get_color()!=color) moves.push_back({aux_f,aux_c});
    }
  }
  pos_moves = moves;
};

bool King::is_attacking(Piece* p){
  return 0;
};