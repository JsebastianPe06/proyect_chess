#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <random>

#include "pieces.h"
#include "game_history.h"

class Piece;

class Player{
  protected:
    std::string name;
    bool is_white;
    std::vector<Piece*> pieces; //save the pieces in order where king is first
    GameHistory hitory;
  
  public:
    Player(std::string name, bool is_white);

    virtual ~Player();
    //getters and setters  
    std::string get_name();
    bool get_color();
    std::vector<Piece*>& get_pieces();
    void start_pieces(Board& b);

    virtual std::array<std::pair<int, int>, 2> play_turn(const Board& board) = 0;
    virtual void paw_promotion(Piece* p, Board& b) = 0;
};

class RealUser: public Player{
  public:
    RealUser(std::string name, bool is_white);

    std::array<std::pair<int, int>, 2> play_turn(const Board& board) override;
    void paw_promotion(Piece* p, Board& b) override;

};

class RandomBot: public Player{
  private:
    std::mt19937 gen;
  
  public:
    RandomBot(bool is_white);

    int random_int(int a, int b);

    std::array<std::pair<int, int>, 2> play_turn(const Board& board) override;
    void paw_promotion(Piece* p, Board& b) override;
};

#endif