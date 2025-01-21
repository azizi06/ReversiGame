#ifndef MINMAX_H
#define MINMAX_H
#include "move.h"
#include"Constants.h"
float evaluate_board(int board[ROWS][COLUMNS], int player);
float minimax(int board[ROWS][COLUMNS], int depth, bool maximizingPlayer, int player) ;
struct Move* best_move(int board[ROWS][COLUMNS], int player,int Depth) ;

void undo_changes(int board[ROWS][COLUMNS],struct Move* move ,struct MSet* changes,int opponent);
int Depth_Controller(int i);

struct Move* minimax_decision(int state[ROWS][COLUMNS],int player,int depth);
#endif // MINMAX_H
