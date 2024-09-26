#include <stdio.h>
#include "GameLoop.h"
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>

#include "minmax.h"

// Function prototypes
void print_board(int board[ROWS][COLUMNS]);
int main() {
    
RandomPlayerWihtMinMaxAgent();
//  playWihtMinMaxAgent();
/* int matrix[ROWS][COLUMNS] = {0};
    matrix[3][3]= W;
    matrix[3][4]= B;
    matrix[4][3]= B;
    matrix[4][4]= W;
printf("\nbefore move : ");
print_board(matrix); 
struct Move* move = new_move(4,5);
struct MSet* changes = perform_action(matrix,move,B);
printf("\nafter move : ");
print_board(matrix);
undo_changes(matrix,move,changes,-B);
printf("\nafter undo : ");
print_board(matrix);
changes->free(changes);
free(changes); */


    return 0;
}


