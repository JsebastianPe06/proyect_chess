#include <stack>
#include <list>
#include <vector>
#include <stdexcept>

#include "game_history.h"

//Save a game to the stack
void GameHistory::save_game(const std::list<std::array<std::pair<int,int>,2>>& movements) {
  games.push(movements);
}

//Check if there are any saved games
bool GameHistory::has_games() const {
  return !games.empty();
}

//Retrieve and remove the last saved game
std::list<std::array<std::pair<int,int>,2>> GameHistory::get_last_game() {
  if (games.empty()) 
    throw std::runtime_error("There are no saved games");  //Throw error if stack is empty
  auto g = games.top();
  games.pop();
  return g;
}

//Retrieve and remove the last n saved games
std::vector<std::list<std::array<std::pair<int,int>,2>>> GameHistory::get_last_n_games(int n) {
  std::vector<std::list<std::array<std::pair<int,int>,2>>> result;
  for (int i = 0; i < n && !games.empty(); ++i) {
    result.push_back(games.top());
    games.pop();
  }
  return result;
}
