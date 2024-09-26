#ifndef MINMAX_H
#define MINMAX_H
#include "move.h"
#include"Constants.h"
float evaluate_board(int board[ROWS][COLUMNS], int player);
int minimax(int board[ROWS][COLUMNS], int depth, bool maximizingPlayer, int player) ;
struct Move* best_move(int board[ROWS][COLUMNS], int player) ;



#endif // MINMAX_H
