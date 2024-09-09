#ifndef REVERSI_H
#define REVERSI_H
#include"map.h"
#include"set.h"



struct Reversi
{
    int game_matrix[ROWS][COLUMNS] ;
    char player ;
    bool winner;
    void (*move)  (struct Move* move);
    
};
struct Reversi* new_reversi(char player);
struct set* avaible_actions(int game_mateix[ROWS][COLUMNS]);
void perform_move(struct Move* move);
bool check_winner(int game_matrix[ROWS][COLUMNS]);
char next_player(int gamme_matrix[ROWS][COLUMNS]);


#endif