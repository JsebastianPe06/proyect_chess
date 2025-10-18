/*
This .h indicates the existence of the Piece classes and its attributes and
methods for using them
*/

#ifndef PIECES_H
#define PIECES_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <list>

class Board;

class Piece{
  protected:
    std::string name;
    bool color; //white = true, black = false
    int f;
    int c;
  public:
    bool is_moves_rook;
    bool is_moves_bishop;
  
  public:
  //Methods set an get of rows(f), columns(c), color and name
  int get_row();
  int get_column();
  void set_row(int new_f);
  void set_column(int new_c);
  std::pair<int,int> get_actual_pos(); //method to get an arrair [row(f), column(c)]
  void set_actual_pos(int new_pos[2]); //method to set actual row(f) and actual column(c)
  bool get_color();
  std::string get_name();


  Piece(bool color, int f, int c);
  virtual ~Piece();
  virtual std::vector<std::pair<int, int>> possible_moves(Board& b) = 0;

    //methods to display in terminal polymorphically
    virtual void display(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Piece& p);
};

class Pawn: public Piece{
  public:
    Pawn(bool color, int f, int c);
  
  public:
    std::vector<std::pair<int, int>> possible_moves(Board& b) override;
    bool get_first_move();
};

class Rook: public Piece{
  public:
    Rook(bool color, int f, int c);
  
  public:
    std::vector<std::pair<int, int>> possible_moves(Board& b) override;
};

class Knight: public Piece{
  public:
    Knight(bool color, int f, int c);
  
  public:
    std::vector<std::pair<int, int>> possible_moves(Board& b) override;
    void display(std::ostream& os) const override;
    friend std::ostream& operator<<(std::ostream& os, Knight& p);
};

class Bishop: public Piece{
  public:
    Bishop(bool color, int f, int c);
  
  public:
    std::vector<std::pair<int, int>> possible_moves(Board& b) override;
};

class Queen: public Piece{
  public:
    Queen(bool color, int f, int c);
  
  public:
    std::vector<std::pair<int, int>> possible_moves(Board& b) override;
};

class King: public Piece{
  public:
    King(bool color, int f, int c);
  
  public:
    std::vector<std::pair<int, int>> possible_moves(Board& b) override;

};

#endif