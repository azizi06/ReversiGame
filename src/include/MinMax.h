#ifndef MINMAX_H
#define MINMAX_H
#include "move.h"
#include"Constants.h"
float evaluate_board(int board[ROWS][COLUMNS], int player);
int Depth_Controller(int i);
struct Move* minimax_decision(int state[ROWS][COLUMNS],int player,int depth);

#endif // MINMAX_H
