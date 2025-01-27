#ifndef REVERSI_H
#define REVERSI_H
#include"map.h"
#include"moveset.h"
#include "move.h"



struct Reversi
{
    int game_matrix[ROWS][COLUMNS] ;
    int player ;
    int winner;
    int score_w;
    int score_b;
    void (*move)  (struct Reversi *self,struct Move* move);
    void (*next) (struct Reversi *self);
    //return false if game over true if not
    bool (*isgame_over) (struct Reversi *self);
    void (*print) (struct Reversi *self);
    void (*count) (struct Reversi *self);

    
};
struct Reversi* new_reversi();
struct MSet* avaible_actions(int game_matrix[ROWS][COLUMNS],int player);
void perform_move(struct Reversi *self,struct Move* move);
void perform_move2(int state[ROWS][COLUMNS], int player, struct Move* move);

bool isgame_over(struct Reversi *self);
bool isgame_over2(int  game_matrix[ROWS][COLUMNS] );

void next_player(struct Reversi *self);
void count_score(struct Reversi *self);
void print_game(struct Reversi *self);
bool is_valid_move(int board[ROWS][COLUMNS], int row, int col, int player);
struct MSet* find_possible_moves(int board[ROWS][COLUMNS], int player);
bool is_correct_input(struct Reversi *self,int row,int col,int player);
void check_winner(struct Reversi *self);
void free_reversi();


#endif