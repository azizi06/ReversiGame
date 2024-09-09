#ifndef REVERSI_H
#define REVERSI_H
#include"map.h"
#include"set.h"
#include "move.h"



struct Reversi
{
    int game_matrix[ROWS][COLUMNS] ;
    int player ;
    int winner;
    int score_w;
    int score_b;
    void (*move)  (struct Reversi *self,struct Move* move);
    int (*next) (struct Reversi *self);
    bool (*isgame_over) (struct Reversi *self);
    void (*print) (struct Reversi *self);
    
};
struct Reversi* new_reversi();
struct Set* avaible_actions(int game_mateix[ROWS][COLUMNS]);
void perform_move(struct Reversi *self,struct Move* move);
bool isgame_over(struct Reversi *self);
int next_player(struct Reversi *self);
int count_score(struct Reversi *self,int Player);
void print_game(struct Reversi *self);


#endif