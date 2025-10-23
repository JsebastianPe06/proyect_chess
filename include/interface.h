#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <list>

#include "game_history.h"

class Interface{
  private:
    GameHistory history;


  public:
    void defined_game();
    void principal_menu();
};

#endif