#ifndef REVERSI_H
#define REVERSI_H
#include"map.h"
#include"set.h"



struct Reversi
{
    int game_matrix[ROWS][COLUMNS] ;
    char player ;
    bool winner;
    void (*move)  (struct Reversi *self,struct Move* move);
    void (*next) (struct Reversi *self);
    void (*check_winner) (struct Reversi *self);
    
};
struct Reversi* new_reversi(char player);
struct set* avaible_actions(int game_mateix[ROWS][COLUMNS]);
void perform_move(struct Reversi *self,struct Move* move);
bool check_winner(struct Reversi *self);
char next_player(struct Reversi *self);


#endif