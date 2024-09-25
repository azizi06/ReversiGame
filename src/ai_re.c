#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define BOARD_SIZE 8
#define BLACK 1
#define WHITE -1
#define EMPTY 0

typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];
} Board;

typedef struct {
    int row, col;
} Move;

typedef struct {
    double q_table[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE][BOARD_SIZE];
    double alpha;
    double gamma;
    double epsilon;
} QAgent;

void initializeBoard(Board *board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board->board[i][j] = EMPTY;
        }
    }

    board->board[3][3] = WHITE;
    board->board[3][4] = BLACK;
    board->board[4][3] = BLACK;
    board->board[4][4] = WHITE;
}

void printBoard(Board *board) {
    printf("  ");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board->board[i][j] == BLACK) {
                printf("B ");
            } else if (board->board[i][j] == WHITE) {
                printf("W ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int isValidMove(Board *board, int row, int col, int player) {
    if (board->board[row][col] != EMPTY) {
        return 0;
    }

    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
    int found = 0;

    for (int d = 0; d < 8; d++) {
        int r = row + directions[d][0];
        int c = col + directions[d][1];

        if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board->board[r][c] == -player) {
            while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board->board[r][c] == -player) {
                r += directions[d][0];
                c += directions[d][1];
            }

            if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board->board[r][c] == player) {
                found = 1;
                break;
            }
        }
    }

    return found;
}

void makeMove(Board *board, int row, int col, int player) {
    board->board[row][col] = player;

    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};

    for (int d = 0; d < 8; d++) {
        int r = row + directions[d][0];
        int c = col + directions[d][1];

        if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board->board[r][c] == -player) {
            while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board->board[r][c] == -player) {
                r += directions[d][0];
                c += directions[d][1];
            }

            if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board->board[r][c] == player) {
                while (r != row || c != col) {
                    r -= directions[d][0];
                    c -= directions[d][1];
                    board->board[r][c] = player;
                }
            }
        }
    }
}

int getValidMoves(Board *board, int player, Move moves[]) {
    int numMoves = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (isValidMove(board, i, j, player)) {
                moves[numMoves].row = i;
                moves[numMoves].col = j;
                numMoves++;
            }
        }
    }

    return numMoves;
}

int isGameOver(Board *board) {
    Move moves[64];
    int numBlackMoves = getValidMoves(board, BLACK, moves);
    int numWhiteMoves = getValidMoves(board, WHITE, moves);

    return numBlackMoves == 0 && numWhiteMoves == 0;
}

int getWinner(Board *board) {
    int blackCount = 0;
    int whiteCount = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board->board[i][j] == BLACK) {
                blackCount++;
            } else if (board->board[i][j] == WHITE) {
                whiteCount++;
            }
        }
    }

    if (blackCount > whiteCount) {
        return BLACK;
    } else if (whiteCount > blackCount) {
        return WHITE;
    } else {
        return 0;
    }
}

void initializeQAgent(QAgent *agent) {
    agent->alpha = 0.1;
    agent->gamma = 0.9;
    agent->epsilon = 0.1;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            for (int k = 0; k < BOARD_SIZE; k++) {
                for (int l = 0; l < BOARD_SIZE; l++) {
                    agent->q_table[i][j][k][l] = 0.0;
                }
            }
        }
    }
}

Move chooseAction(QAgent *agent, Board *board, int player) {
    Move moves[64];
    int numMoves = getValidMoves(board, player, moves);

    if (rand() < RAND_MAX * agent->epsilon) {
        return moves[rand() % numMoves];
    } else {
        double maxQ = -INFINITY;
        Move bestMove;

        for (int i = 0; i < numMoves; i++) {
            int row = moves[i].row;
            int col = moves[i].col;
            double qValue = agent->q_table[board->board[row][col]][board->board[moves[i].row][moves[i].col]][board->board[moves[i].row][moves[i].col]][board->board[moves[i].row][moves[i].col]];

            if (qValue > maxQ) {
                maxQ = qValue;
                bestMove = moves[i];
            }
        }

        return bestMove;
    }
}

void updateQTable(QAgent *agent, Board *board, Move move, int player, double reward) {
    int row = move.row;
    int col = move.col;
    double oldQValue = agent->q_table[board->board[row][col]][board->board[move.row][move.col]][board->board[move.row][move.col]][board->board[move.row][move.col]];

    makeMove(board, move.row, move.col, player);

    Move nextMoves[64];
    int numNextMoves = getValidMoves(board, -player, nextMoves);

    double maxNextQValue = -INFINITY;
    for (int i = 0; i < numNextMoves; i++) {
        int nextRow = nextMoves[i].row;
        int nextCol = nextMoves[i].col;
        double nextQValue = agent->q_table[board->board[nextRow][nextCol]][board->board[nextMoves[i].row][nextMoves[i].col]][board->board[nextMoves[i].row][nextMoves[i].col]][board->board[nextMoves[i].row][nextMoves[i].col]];
        maxNextQValue = fmax(maxNextQValue, nextQValue);
    }

    makeMove(board, move.row, move.col, -player);

    double newQValue = oldQValue + agent->alpha * (reward + agent->gamma * maxNextQValue - oldQValue);

    agent->q_table[board->board[row][col]][board->board[move.row][move.col]][board->board[move.row][move.col]][board->board[move.row][move.col]] = newQValue;
}
void trainAgent(QAgent *agent) {
    int numGames = 100000;

    for (int i = 0; i < numGames; i++) {
        Board board;
        initializeBoard(&board);

        while (!isGameOver(&board)) {
            int player = i % 2 == 0 ? BLACK : WHITE;
            Move move = chooseAction(agent, &board, player);
            makeMove(&board, move.row, move.col, player);

            int winner = getWinner(&board);
            double reward = winner == player ? 1.0 : (winner == 0 ? 0.0 : -1.0);

            updateQTable(agent, &board, move, player, reward);
        }
    }
}

void playGame(QAgent *agent) {
    Board board;
    initializeBoard(&board);

    while (!isGameOver(&board)) {
        printBoard(&board);

        int player = BLACK; // Human player starts
        Move move;

        if (player == BLACK) {
            printf("Enter row and column (e.g., 3 4): ");
            scanf("%d %d", &move.row, &move.col);

            if (!isValidMove(&board, move.row, move.col, player)) {
                printf("Invalid move. Try again.\n");
                continue;
            }
        } else {
            move = chooseAction(agent, &board, player);
            printf("AI player: %d %d\n", move.row, move.col);
        }

        makeMove(&board, move.row, move.col, player);
        player = -player; // Switch players
    }

    int winner = getWinner(&board);
    printf("Game over!\n");

    if (winner == BLACK) {
        printf("Human player wins!\n");
    } else if (winner == WHITE) {
        printf("AI player wins!\n");
    } else {
        printf("Draw!\n");
    }
}

int main() {
    srand(time(NULL));

    QAgent agent;
    initializeQAgent(&agent);

    trainAgent(&agent);

    playGame(&agent);

    return 0;
}