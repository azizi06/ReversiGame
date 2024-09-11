#include <stdio.h>

#define ROWS  8
#define COLUMNS  8
#define W  -1  /**@breif White player */
#define B   1 /**@breif Black player */
#define P 0 /**@breif Possible Moves */
#define H 9 /**@breif Empty cell  */
#define None 9999

#include <stdio.h>
#include <stdbool.h>


// Function prototypes
bool is_valid_move(int board[ROWS][COLUMNS], int row, int col, int player);
void find_possible_moves(int board[ROWS][COLUMNS], int player, int possible_moves[ROWS * COLUMNS][2], int* num_moves);

bool is_valid_move(int board[ROWS][COLUMNS], int row, int col, int player) {
    if (board[row][col] != 0) {
        return false; // The cell is not empty
    }

    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    int opponent = (player == W) ? B : W;

    for (int d = 0; d < 8; d++) {
        int dr = directions[d][0];
        int dc = directions[d][1];
        int r = row + dr;
        int c = col + dc;
        bool found_opponent = false;

        while (r >= 0 && r < ROWS && c >= 0 && c < COLUMNS) {
            if (board[r][c] == opponent) {
                found_opponent = true;
            } else if (board[r][c] == player && found_opponent) {
                return true; // Valid move if we found the player's disk after opponent's disks
            } else {
                break;
            }

            r += dr;
            c += dc;
        }
    }

    return false;
}

void find_possible_moves(int board[ROWS][COLUMNS], int player, int possible_moves[ROWS * COLUMNS][2], int* num_moves) {
    *num_moves = 0;

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            if (is_valid_move(board, row, col, player)) {
                possible_moves[*num_moves][0] = row;
                possible_moves[*num_moves][1] = col;
                (*num_moves)++;
            }
        }
    }
}

int main() {
    int board[ROWS][COLUMNS] = { 
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, W, W, W, B, 0, 0, 0},
        {0, 0, 0, B, W, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int possible_moves[ROWS * COLUMNS][2];
    int num_moves;
     printf("hooa");
    find_possible_moves(board, B, possible_moves, &num_moves);

    printf("Possible moves for player %d:\n", B);
    for (int i = 0; i < num_moves; i++) {
        printf("Move at: (%d, %d)\n", possible_moves[i][0], possible_moves[i][1]);
    }

    return 0;
}



