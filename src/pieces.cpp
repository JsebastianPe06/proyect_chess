/*
This .cpp contains the Piece classes, with methods for calculate possible
movements and save states for determinate valid movements
*/

#include <iostream>
#include <string>
#include <array>
#include <vector>

#include "pieces.h"
#include "board.h"


//----------Piece-------------
Piece::Piece(bool color, int f, int c){
  this -> color = color;
  this -> f = f;
  this -> c = c;
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

void Piece::display(std::ostream& os) const{
    os << name[0] << (color ? 'w' : 'b');
}
std::ostream& operator<<(std::ostream& os, const Piece& p){
  p.display(os);
  return os;
};


// ------------------------------ piece pawn ---------------------------------
Pawn::Pawn(bool color, int f, int c): Piece(color, f, c){
  name = "Pawn";
  is_moves_bishop = 0;
  is_moves_rook = 0;
};


std::vector<std::pair<int, int>> Pawn::possible_moves(Board& b){
  /*Method that return the pawn's movement including possibles passant
  and pawn promotion*/
  //int dir = color? -1:1;
  //int start_f = color? 6:1;
  //std::vector<std::pair<int, int>> moves;

  //advance one square
  return {};
};

//------------------------- piece rook ------------------------------------
Rook::Rook(bool color, int f, int c): Piece(color, f, c){
  name = "Rook";
  is_moves_bishop = 0;
  is_moves_rook = 1;
};
std::vector<std::pair<int, int>> Rook::possible_moves(Board& b){
  return {};
};

//------------------------- piece kinght -----------------------------------
Knight::Knight(bool color, int f, int c): Piece(color, f, c){
  name = "Knight";
  is_moves_bishop = 0;
  is_moves_rook = 0;
};
std::vector<std::pair<int, int>> Knight::possible_moves(Board& b){
  return {};
}

void Knight::display(std::ostream& os) const {
    os << 'N' << (color ? 'w' : 'b');
}

//---------------------------- piece bishop --------------------------------
Bishop::Bishop(bool color, int f, int c): Piece(color, f, c){
  name = "Bishop";
  is_moves_bishop = 1;
  is_moves_rook = 0;
};
std::vector<std::pair<int, int>> Bishop::possible_moves(Board& b){
  return {};
};

//------------------------------ piece queen -------------------------------
Queen::Queen(bool color, int f, int c): Piece(color, f, c){
  name = "Queen";
  is_moves_bishop = 1;
  is_moves_rook = 1;
};
std::vector<std::pair<int, int>> Queen::possible_moves(Board& b){
  return {};
};

//----------------------------- piece king ---------------------------------
King::King(bool color, int f, int c): Piece(color, f, c){
  name = "King";
  is_moves_bishop = 0;
  is_moves_rook = 0;
};
std::vector<std::pair<int, int>> King::possible_moves(Board& b){
  return {};
};