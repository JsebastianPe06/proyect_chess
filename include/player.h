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

#include "pieces.h"

class Piece;

class Player{
  protected:
    std::string name;
    bool is_white;
    Piece* king;
  
  public:
    std::string get_name();
    bool get_color();
    Piece* get_king();
  
    
};

#endif