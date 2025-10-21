#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>

#include "game.h"
#include "player.h"
#include "board.h"

Game::Game(Player* p1, Player* p2){
  white_player = p1;
  black_player = p2;
  turn = true;
  counter_irrelevant_moves = 0;
  b_game.starting_position();
};

Game::~Game(){
  
};

std::vector<std::pair<int,int>> Game::val_square_check(Piece* p, std::pair<int,int> sq){
  /*Auxiliary method that, given a defending piece and a target square,
  returns the sequence of squares in the direction that passes through the
  given square. Starting from the p (excluding its current square), it
  continues step by step until reaching:
  - an empty square: added to the vector;
  - an enemy piece: added and stop;
  - an allied piece: stop without adding it.
  It is typically used to determine possible blocking squares in checks or pins.
  */
  std::vector<std::pair<int,int>> val_sq;
  int f = p->get_row();
  int c = p->get_column();
  int tf = sq.first;
  int tc = sq.second;
  //Determine direction vector (step_f, step_c)
  int df = (tf>f)? 1:(tf<f)? -1:0;
  int dc = (tc>c)? 1:(tc<c)? -1:0;
  //If the square is not aligned (same row, column, or diagonal), return empty
  if(!((df==0 && dc!=0) || (df!=0 && dc==0) || (std::abs(df)==std::abs(dc)))) return val_sq;
  //Traverse in the direction defined by (df, dc)
  int i = f+df;
  int j = c+dc;
  auto& b = b_game.get_board();
  while(i>=0 && i<8 && j>=0 && j<8){
    Piece* pc = b[i][j];
    if(pc==nullptr){
      val_sq.push_back({i, j});
    } 
    else{
      if(pc->get_color()!=p->get_color()){
        // Enemy piece: include and stop
        val_sq.push_back({i, j});
      }
      // Ally piece: stop but do not include
      break;
    }
    i += df;
    j += dc;
  }
  return val_sq;
};

std::vector<std::pair<int, int>> Game::val_square_pin(Piece* p){
  /*Uses the val_square_check method to calculate the valid moves of a pinned
  piece, it is a method that takes into account the fact that the received piece
  is pinned*/
  //Calculate from the king to the pinned piece
  Piece* pl = p->get_color()? white_player->get_pieces()[0]:black_player->get_pieces()[0];
  std::vector<std::pair<int,int>> val_sq = val_square_check(pl, p->get_actual_pos());
  //Calculate from the pinned piece to the threatening one
  int tf = pl->get_row();
  int tc = pl->get_column();
  int pf = p->get_row();
  int pc = p->get_column();
  int df = (pf>tf)? 1:(pf<tf)? -1:0;
  int dc = (pc>tc)? 1:(pc<tc)? -1:0;
  std::pair<int, int> s = {tf+df, tc+dc};
  std::vector<std::pair<int,int>> aux = val_square_check(p, s);
  val_sq.insert(val_sq.end(), aux.begin(), aux.end());
  return val_sq;
};


std::vector<std::pair<int, int>> Game::val_sq(std::pair<int, int> a_pos,
std::pair<int, int> n_pos){
  /*After a move, if the enemy king is in check, it looks for possible squares
  that can be occupied in the next turn. If there are no squares, then it
  returns an empty array the king must move*/
  //n_pos is the new move of the moved piece in the turn
  int n_f = n_pos.first;
  int n_c = n_pos.second;
  auto& b = b_game.get_board();
  Piece* k = turn? white_player->get_pieces()[0]:black_player->get_pieces()[0];
  std::vector<std::pair<int,int>> moves;
  bool val_sliding = b[n_f][n_c]->is_moves_bishop || b[n_f][n_c]->is_moves_rook;
  bool val_exposed = b_game.is_sliding_attack(a_pos, k);
  if(val_sliding && val_exposed) return {};
  if(b[n_f][n_c]!=nullptr){
    //whether is sliding piece
    if(val_sliding){
      moves = val_square_check(k, n_pos);
    }
    //whether is pawn or knight
    else if(b[n_f][n_c]->get_name()!="King"){
      moves = {n_pos};
    }
    if(val_exposed) moves = val_square_check(k, a_pos);
    //whether the moved piece generate a exposed check
    return moves;
  };
  return moves;
};

bool Game::analyze_check(std::pair<int, int> a_pos, std::pair<int, int> p_pos){
  /*returns if there is check*/
  Piece* k = turn? black_player->get_pieces()[0]:white_player->get_pieces()[0];
  if(b_game.get_board()[p_pos.first][p_pos.second] != nullptr){
    Piece* p = b_game.get_board()[p_pos.first][p_pos.second];
    if(p->is_moves_bishop==1 || p->is_moves_rook==1) return b_game.is_sliding_attack(p_pos, k);
    else if(p->is_attacking(k)) return true;
  }
  return b_game.is_sliding_attack(a_pos, k);
};

void Game::move_piece(Piece* p, std::pair<int, int> new_p){
  /*This method moves a piece to a new position, exchanges pointers, and deletes
  captured pieces. It also controls the counters and pawn promotions.*/
  int nf = new_p.first;
  int nc = new_p.second;
  auto& board = b_game.get_board();
  Piece* pi = board[nf][nc];
  //Check if there is a capture
  if(pi != nullptr){
    Player* enemy = pi->get_color()? white_player:black_player;
    auto& enemy_pieces = enemy->get_pieces();
    for(size_t i=1; i<enemy_pieces.size(); ++i){ //Skip index 0 (the king)
      if(enemy_pieces[i] == pi){
        enemy_pieces[i] = enemy_pieces.back();
        enemy_pieces.pop_back();
        break;
      }
    }
    delete pi;
    board[nf][nc] = nullptr;
    counter_irrelevant_moves = 0;
  }
  else if(p->get_name() == "Pawn"){
    counter_irrelevant_moves = 0;
    if(p->get_row() == 6 && nf == 7 && p->get_color() == 0)
      black_player->paw_promotion(p);
    else if(p->get_row() == 1 && nf == 0 && p->get_color() == 1)
      white_player->paw_promotion(p);
  }
  else counter_irrelevant_moves += 1;
  int a = p->get_row();
  int b = p->get_column();
  p->set_row(nf);
  p->set_column(nc);
  board[nf][nc] = board[a][b];
  board[a][b] = nullptr;
}

void Game::valid_move_piece(Piece* p, std::vector<std::pair<int, int>> aux_m){
  auto& b = b_game.get_board();
  std::vector<std::pair<int, int>> moves;
  if(p->is_moves_bishop==1 || p->is_moves_rook){
    for(size_t i=1; i<aux_m.size(); i++){
      int f = aux_m[i].first;
      int c = aux_m[i].second;
      if(b[f][c]!= nullptr){
        if(b_game.is_sliding_attack(p->get_actual_pos(), b[f][c])) moves.push_back(aux_m[i]);
      }
      else{
        Piece* aux_p = new Pawn(p->get_color()? 1:0, f, c);
        b[f][c] = aux_p;
        if(b_game.is_sliding_attack(p->get_actual_pos(),b[f][c])) moves.push_back(aux_m[i]);
        delete aux_p;
        b[f][c] = nullptr;
      }
    }
  }
  else{
    for(size_t i=1; i<aux_m.size(); i++){
      int f = aux_m[i].first;
      int c = aux_m[i].second;
      if(b[f][c]!= nullptr){
        if(p->is_attacking(b[f][c])) moves.push_back(aux_m[i]);
      }
      else{
        Piece* aux_p = new Pawn(p->get_color()? 1:0, f, c);
        if(p->is_attacking(aux_p)) moves.push_back(aux_m[i]);
        delete aux_p;
      }
    }
  }
  p->set_moves(moves); 
};

char Game::start_game(){
  /*Given all the functions to be able to play, this method uses all methods to
  compile until there is a winner or a draw*/
  std::vector<Piece*>& p = white_player->get_pieces();
  for(int i=0; i<16; i++){
    p[i]->possible_moves(b_game);
  }
  while(true){
    Player* current = turn? white_player:black_player;
    Player* opponent = turn? black_player:white_player;
    bool is_checkmate = true; //If there is check, the move check controls this variable
    bool is_draw = true;
    //Play a move: returns a pair of positions (actual_pos, new_pos)
    //
    std::pair<int, int> a_p = movements.top()[0];
    std::pair<int, int> n_p = movements.top()[1];
    //Check that the move is valid and the origin piece belongs to the player
    if(a_p.first<0 || a_p.first>7 || a_p.second<0 || a_p.second>7) return 'D';
    if(n_p.first<0 || n_p.first>7 || n_p.second<0 || n_p.second>7) return 'D';
    Piece* moving_piece = b_game.get_board()[a_p.first][a_p.second];
    if(moving_piece==nullptr || moving_piece->get_color()!=current->get_color()) return 'D';
    //Analyze if the move produces a check to the opponent king
    bool val_check = analyze_check(a_p, n_p);
    std::vector<Piece*>& o = opponent->get_pieces();
    Piece* king = o[0];
    king->possible_moves(b_game);
    //If there is check after the move
    if(val_check){
      std::vector<std::pair<int, int>> aux_m = val_sq(a_p, n_p);
      for(size_t i=1; i<o.size(); i++){
        if(!(o[i]->is_pinned(b_game, king))){ //o[0] is king
          valid_move_piece(o[i], aux_m);
        }
        else{
          std::vector<std::pair<int,int>> val_pin = val_square_pin(o[i]);
          valid_move_piece(o[i], val_pin);
        }
        if(!(o[i]->get_moves().empty())) is_checkmate = false;
      }
      if(is_checkmate) return current->get_color()? 'W':'B'; 
    }
    //If there is not check
    else{
      for(size_t i=1; i<o.size(); i++){
        if(!(o[i]->is_pinned(b_game, king))){
          o[i]->possible_moves(b_game);
        }
        else{
          std::vector<std::pair<int,int>> val_pin = val_square_pin(o[i]);
          valid_move_piece(o[i], val_pin);
        }
        if(!(o[i]->get_moves().empty())) is_draw = false;
      }
      if(is_draw || (counter_irrelevant_moves==50)) return 'D';
    }
    //After the validations, the move is executed
    move_piece(moving_piece, n_p);
    //Update the moves for the next player
    for(size_t i=0; i<o.size(); i++){
      o[i]->possible_moves(b_game);
    }
    //Change turn
    turn = !turn;
  }
}