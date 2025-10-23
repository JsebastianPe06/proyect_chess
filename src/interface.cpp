#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <list>

#include "interface.h"
#include "game.h"
#include "player.h"
#include "board.h"


void Interface::defined_game(){
  int option = 0;
  while(option!=3){
    std::cout << "====================================\n" << std::endl;
    std::cout << "              SETTING               \n" << std::endl;
    std::cout << "====================================\n" << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << "1. in turns\n" << std::endl;
    std::cout << "2. vs RandomBot\n" << std::endl;
    std::cout << "3. Exit\n" << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << "Enter an option (1-3): ";
    std::cin >> option;
    if(option==1){
      Player* p1 = new RealUser("player1", 1);
      Player* p2 = new RealUser("player2", 0); 
      Game gm(p1, p2, &history);
      gm.start_game();
    }
    else if(option==2){
      bool start;
      std::cout << "Start RandomBot(1 yes: 0:no)?: ";
      std::cin >> start;
      if(start){
        Player* p1 = new RandomBot(1);
        Player* p2 = new RealUser("player", 0); 
        Game gm(p1, p2, &history);
        gm.start_game();
        delete p1;
        delete p2;
      }
      else{
        Player* p1 = new RandomBot(0);
        Player* p2 = new RealUser("player", 1); 
        Game gm(p1, p2, &history);
        gm.start_game();
        delete p1;
        delete p2;
      }
    }
  }
}

void Interface::principal_menu(){
  bool exit = false;
  while(!exit){
    int option;
    std::cout << "====================================\n" << std::endl;
    std::cout << "           CHESS GAME               \n" << std::endl;
    std::cout << "====================================\n" << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << "1. Play\n" << std::endl;
    std::cout << "2. History game\n" << std::endl;
    std::cout << "3. Exit\n" << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << "Enter an option (1-3): ";
    std::cin >> option;
    if(option==1){
      defined_game();
    }

    else if(option==2){
      if(!history.has_games()){
        std::cout << "No games in history.\n";
      }
      else{
        int n;
        std::cout << "How many last games to display? ";
        std::cin >> n;
        auto last_games = history.get_last_n_games(n);
        int game_number = 1;
        for(auto &game_moves : last_games){
          std::cout << "Game " << game_number++ << " moves:\n";
          for(auto &move : game_moves){
            std::cout << "(" << move[0].first << "," << move[0].second << ") -> "
              << "(" << move[1].first << "," << move[1].second << ")\n";
          }
          std::cout << "---------------------\n";
        }
      }
    }
    else{
      exit = true;
    }
  }
};