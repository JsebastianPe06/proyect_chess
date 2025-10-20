/*
This .h indicates the existence of the Board class and its attributes and
methods for using them
*/

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "pieces.h"

class Board{
  protected:
    Piece* board[8][8];
    friend std::ostream& operator<<(std::ostream& os, const Board& p);
    
  public:
    Board();
    virtual ~Board();

    //getters and setters
    Piece* (&get_board())[8][8]{
      return board;
    };

    //starting positions methods
    void starting_pawn();
    void starting_rook();
    void starting_knight();
    void starting_bishop();
    void starting_king();
    void starting_queen();
    void starting_position();

    //special methods to analyze possible x-ray attacks or checks and checkmates
    bool attack_row(const std::pair<int,int> square,Piece* attacked);
    bool attack_column(const std::pair<int,int> square,Piece* attacked);
    bool attack_major_diagonal(const std::pair<int,int> square, Piece* attacked);
    bool attack_minor_diagonal(const std::pair<int,int> square, Piece* attacked);
    bool is_sliding_attack(const std::pair<int,int> square, Piece* attacked);
    
    void move_piece(Piece* p, std::pair<int, int>);
};

#endif