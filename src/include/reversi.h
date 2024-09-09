#ifndef REVERSI_H
#define REVERSI_H
#include"map.h"
#include"set.h"

struct reversi
{
    int game_matrix[ROWS][COLUMNS] ;
    
};
struct set* avaible_actions(int game_mateix[ROWS][COLUMNS]);
void move();

#endif