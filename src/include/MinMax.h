#ifndef MINMAX_H
#define MINMAX_H
#include "move.h"
#include"Constants.h"
float evaluate_board(int board[ROWS][COLUMNS], int player);
int minimax(int board[ROWS][COLUMNS], int depth, bool maximizingPlayer, int player) ;
struct Move* best_move(int board[ROWS][COLUMNS], int player,int Depth) ;

bool is_game_over(int board[ROWS][COLUMNS]);
struct MSet* perform_action(int game_matrix[ROWS][COLUMNS],struct Move* move,int player);
void undo_changes(int board[ROWS][COLUMNS],struct Move* move ,struct MSet* changes,int opponent);
int Depth_Controller(int i);
#endif // MINMAX_H
