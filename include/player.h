/*
This .h indicates the existence of the player class and bot class and its
attributes and methods for using them
*/
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>

#include "pieces.h"

class Piece;

class Player{
  protected:
    std::string name;
    bool is_white;
    std::vector<Piece*> pieces; //save the pieces in order where king is first
  
  public:
    Player(std::string name, bool is_white);

    //getters and setters  
    std::string get_name();
    bool get_color();
    std::vector<Piece*>& get_pieces();
    void start_pieces(Board& b);

    virtual std::array<std::pair<int, int>, 2> play_turn() = 0;
    virtual void paw_promotion(Piece* p) = 0;
};

class RealUser: public Player{
  public:
    RealUser(std::string name, bool is_white);

    std::array<std::pair<int, int>, 2> play_turn() override;
    virtual void paw_promotion(Piece* p) override;

};

class RandomBot: public Player{
  public:
    RandomBot(bool is_white);

    std::array<std::pair<int, int>, 2> play_turn() override;
    virtual void paw_promotion(Piece* p) override;
};

#endif