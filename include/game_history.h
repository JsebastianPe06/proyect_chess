#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H

#include <stack>
#include <list>
#include <vector>
#include <array>
#include <utility>
#include <stdexcept>

class GameHistory {
private:
  //Stack to store games, each game is a list of moves (each move is an array of two pairs of integers)
  std::stack<std::list<std::array<std::pair<int,int>,2>>> games;

public:
  //Save a game
  void save_game(const std::list<std::array<std::pair<int,int>,2>>& movements);

  //Check if there are saved games
  bool has_games() const;

  //Get and remove the last saved game
  std::list<std::array<std::pair<int,int>,2>> get_last_game();

  //Get and remove the last n saved games
  std::vector<std::list<std::array<std::pair<int,int>,2>>> get_last_n_games(int n);
};

#endif

