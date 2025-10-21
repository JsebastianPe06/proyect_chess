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
    int value;
    std::vector<std::pair<int, int>> pos_moves;

  public:
    bool is_moves_rook;
    bool is_moves_bishop;
  
  public:
    //Methods set an get of rows(f), columns(c), color, value and name
    int get_row();
    int get_column();
    void set_row(int new_f);
    void set_column(int new_c);
    std::pair<int,int> get_actual_pos(); //method to get an arrair [row(f), column(c)]
    void set_actual_pos(int new_pos[2]); //method to set actual row(f) and actual column(c)
    bool get_color();
    std::string get_name();
    int get_value();
    std::vector<std::pair<int, int>> get_moves();
    void set_moves(std::vector<std::pair<int, int>> m);


    Piece(bool color, int f, int c, int value);
    virtual ~Piece();
    virtual void possible_moves(Board& b) = 0;

    //methods to display in terminal polymorphically
    virtual void display(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Piece& p);

    //method to know whether the piece is pinned
    bool is_pinned(Board& b, Piece* p);

    //specific method of the pawn and knight
    virtual bool is_attacking(Piece* p) = 0;
};

class Pawn: public Piece{
  public:
    Pawn(bool color, int f, int c);
  
  public:
    void possible_moves(Board& b) override;
    bool get_first_move();
    bool is_first_move;
  
    bool is_attacking(Piece* p) override;
};

class Rook: public Piece{
  protected:
    static const std::pair<int, int> dir[4]; //directions by calculate moves
  
  public:
    Rook(bool color, int f, int c);
  
  public:
    void possible_moves(Board& b) override;

    bool is_attacking(Piece* p) override;
};

class Knight: public Piece{
  protected:
    static const std::pair<int, int> dir[8]; //directions by calculate moves
  
  public:
    Knight(bool color, int f, int c);
  
  public:
    void possible_moves(Board& b) override;
    void display(std::ostream& os) const override;
    friend std::ostream& operator<<(std::ostream& os, Knight& p);
    
    bool is_attacking(Piece* p) override;
};

class Bishop: public Piece{
  protected:
    static const std::pair<int, int> dir[4]; //directions by calculate moves

  public:
    Bishop(bool color, int f, int c);
  
  public:
    void possible_moves(Board& b) override;
    bool is_attacking(Piece* p) override;
};

class Queen: public Piece{
  protected:
    static const std::pair<int, int> dir[8]; //directions by calculate moves
  public:
    Queen(bool color, int f, int c);
  
  public:
    void possible_moves(Board& b) override;

    bool is_attacking(Piece* p) override;
};

class King: public Piece{
  protected:
    static const std::pair<int, int> dir[8]; //directions by calculate moves
  
  public:
    King(bool color, int f, int c);
  
  public:
    void possible_moves(Board& b) override;

    bool is_attacking(Piece* p) override;

};

#endif