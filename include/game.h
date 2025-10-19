/*
This .h indicates the existence of the Game class and its attributes and
methods for using them
*/
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "board.h"
#include "pieces.h"
#include "player.h"

class Board;
class Piece;
class Player;

class Game{
  public:
    Board b_game;

  protected:
    Player* white_player;
    Player* black_player;
    bool turn; //white = true, black = false
    int counter_irrelevant_moves; //
  
  public:
    

    bool analyze_check();
    bool analyze_draw();
    void play_turn();
};

#endif