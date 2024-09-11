#ifndef TOOLS_H
#define TOOLS_H
#include "Constants.h"
#include "moveSet.h"
int print_matrix(int matrix[ROWS][COLUMNS]);
int compare_2d_array(int arr1[ROWS][COLUMNS], int arr2[ROWS][COLUMNS]);
struct MSet* point_neighbors(int matrix[ROWS][COLUMNS],struct Move* move,int player);

#endif