#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>

#include "board.h"
#include "pieces.h"
#include "player.h"

class Board;
class Piece;
class Player;

class Game{
  public:
    Board b_game;
    bool turn; //white = true, black = false

  protected:
    Player* white_player;
    Player* black_player;
    int counter_irrelevant_moves; //counter to know whether there is draw by 50 plays
    std::stack<std::array<std::pair<int, int>,2>> movements; //save the moves made in the game
  
  public:
    Game(Player* p1, Player* p2);
    ~Game();

    std::vector<std::pair<int, int>> val_sq(std::pair<int, int> a_pos, std::pair<int, int> n_pos);
    std::vector<std::pair<int, int>> val_square_check(Piece* p, std::pair<int, int> sq);
    std::vector<std::pair<int, int>> val_square_pin(Piece* p);
    bool analyze_check(std::pair<int, int> a_pos, std::pair<int, int> p_pos);
    void remove_plays();
    char start_game();
    void move_piece(Piece* p, std::pair<int, int> new_p);
    void valid_move_piece(Piece* p, std::vector<std::pair<int, int>> val_m);
};

#endif