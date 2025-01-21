#ifndef TOOLS_H
#define TOOLS_H
#include <stdio.h>
#include "Constants.h"
#include "moveSet.h"
#include"reversi.h"
#define ABS(x) ((x) < 0 ? -(x) : (x))
int print_matrix(int matrix[ROWS][COLUMNS]);
int compare_2d_array(int arr1[ROWS][COLUMNS], int arr2[ROWS][COLUMNS]);
void copy_2d_array(int destination[ROWS][COLUMNS], int origine[ROWS][COLUMNS]);
struct MSet* point_neighbors(int matrix[ROWS][COLUMNS],struct Move* move,int player);
int get_input(char *prompt, char *input_buffer, size_t buffer_size);
int handel_player_input(struct Reversi *self,char *input_x, char *input_y);
int choose_random(float p);
int (*allocate_matrix(int rows, int cols))[COLUMNS];

// Function to free the allocated 2D array
void free_matrix(int (*matrix)[COLUMNS]);
void print_board(int board[ROWS][COLUMNS]);
#endif