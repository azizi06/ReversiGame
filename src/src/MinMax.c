#include<stdio.h>
#include<stdlib.h>
#include<moveSet.h>
#include "Constants.h"
#include<stdbool.h>
#include "reversi.h"
#include"tools.h"
#include"MinMax.h"
// W min Player
// B MAX Player
float evaluate_board(int board[ROWS][COLUMNS], int player);
float minimax(int board[ROWS][COLUMNS], int depth, bool maximizingPlayer, int player) ;
struct Move* best_move(int board[ROWS][COLUMNS], int player,int Depth) ;
bool is_game_over(int board[ROWS][COLUMNS]);
struct MSet* perform_action(int game_matrix[ROWS][COLUMNS],struct Move* move,int player);
void undo_changes(int board[ROWS][COLUMNS],struct Move* move,struct MSet* changes,int opponent);

void mark_stable(int board[ROWS][COLUMNS], bool stable[ROWS][COLUMNS], int player, int x, int y);
int count_stable_discs(int board[ROWS][COLUMNS], int player);
int Depth_Controller(int i);
int Depth_Controller(int i){
    int Depth;
    if(i<20){Depth = 3;}
    else if(i<30){Depth = 3;}
    else if(i<40){Depth = 4;}
    else { Depth = 5;}

    //printf("\n i : %d , Depth : %d",i,Depth);
    return Depth;
}
float minimax(int board[ROWS][COLUMNS], int depth, bool maximizingPlayer, int player) {
    if (depth == 0 || is_game_over(board)) {
        return evaluate_board(board, player);  // Evaluate the board if depth is 0 or game over
    }

    struct MSet* available_actions = find_possible_moves(board, player);
    struct msnode* current = available_actions->head;

    if (maximizingPlayer) {
        float maxEval = -10000.0f;
        while (current != NULL) {
            struct Move* action = current->value;
            struct MSet* changes = perform_action(board, action, player);
            
            float eval = minimax(board, depth - 1, false, -player);  // Recursively call minimax
            undo_changes(board, action, changes, -player); 
            changes->free(changes);
            free(changes);
            if(1 == eval){ return eval;}
            maxEval = (eval > maxEval) ? eval : maxEval;
            current = current->next;
        }
        available_actions->free(available_actions);
        free(available_actions);
        return maxEval;
    } else {
        float minEval = 10089.0f;
        while (current != NULL) {
            struct Move* action = current->value;
            struct MSet* changes = perform_action(board, action, player);
            
            float eval = minimax(board, depth - 1, true, -player);  
            undo_changes(board, action, changes, -player);  
            changes->free(changes);
            free(changes);
            if(-1 == eval) return eval;
            minEval = (eval < minEval) ? eval : minEval;
            current = current->next;
        }
        available_actions->free(available_actions);
        free(available_actions);
        return minEval;
    }
}

//B is max player W is min player
struct Move* best_move(int board[ROWS][COLUMNS], int player,int Depth) {
    float bestValue ; //(player == B) ? -10000 : 10000;
    if(player == B){
       // printf("\nB best value");
        bestValue = -10000.0f;}
    else if(player == W){
        //printf("\nW best value");
          bestValue = 10000456.0f;
    }
    int bestRow = -1, bestCol = -1;
    struct MSet* available_actions = find_possible_moves(board, player);
    bool isMaximizing = (player == B) ?  true : false;
    if (available_actions->size == 0) {
        printf("ERROR : NO avaible actions found");
        return NULL;  // No available actions
    }

    struct msnode* current = available_actions->head;

    while (current != NULL) {
        struct Move* action = current->value;
        struct MSet* changes = perform_action(board, action, player);
        
        float moveValue = minimax(board, Depth, isMaximizing, -player);  
        
        undo_changes(board, action, changes, -player);  
        changes->free(changes);
        free(changes);
        if((player == B && moveValue == 1) || (player == W && moveValue == -1)){
            bestValue = moveValue;
            bestRow = action->x;
            bestCol = action->y;
            break;
        }
        
      
        if (player == B && moveValue > bestValue) {
            bestValue = moveValue;
            bestRow = action->x;
            bestCol = action->y;
        } else if (player == W && moveValue < bestValue) {
            bestValue = moveValue;
            bestRow = action->x;
            bestCol = action->y;
        }

        current = current->next;
    }
    //free MSet
    available_actions->free(available_actions);
    free(available_actions);

    if (bestRow == -1 || bestCol == -1) {
        printf("EROOR: NO valid move found");
        return NULL;  // No valid move found
    }
 

    FILE *fp;
    fp = fopen("data.txt","a");
    fprintf(fp,"\nmove (%d,%d) : value : %f",bestRow,bestCol,bestValue);  
    fclose(fp);
    return new_move(bestRow, bestCol);  // Return the best move
}


  
bool is_game_over(int board[ROWS][COLUMNS]){
    int numberOfCells = ROWS*COLUMNS;
    int score_b = 0;
    int score_w = 0;
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLUMNS;j++){
            if(W == board[i][j]){
                score_w++;
            }else if(B == board[i][j]){
                score_b++;
            }

        }
    }
    if(score_b == 0 || score_w == 0 || (score_b+score_w) == numberOfCells){
        return true;
    }
    return false;
    
};
struct MSet* perform_action(int game_matrix[ROWS][COLUMNS],struct Move* move,int player){
    struct MSet* changes = new_mset();
    game_matrix[move->x][move->y] = player;
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };
    int opponent = (player == W)? B:W;
    for(int d= 0 ;d<8;d++){
        int dr = directions[d][0];
        int dc = directions[d][1];
        int r = move->x + dr;
        int c = move->y + dc;
        struct MSet* remember = new_mset();

        bool found_player = false;
        while (r<ROWS && r>=0 && c<COLUMNS && c >=0){
              if(game_matrix[r][c] == E){
                break;
            } 
            else if(game_matrix[r][c] == opponent){
                remember->append(remember,new_move(r,c));
            }else if(game_matrix[r][c]== player){
                found_player = true;
            }   
            r +=dr;
            c +=dc;        
        }
        //marking the changes :
        if(found_player){
            struct msnode* current = remember->head;
            while (current!=NULL){
                struct Move* point = current->value;  
                game_matrix[point->x][point->y] = player;
                changes->append(changes,new_move(point->x,point->y));
                current = current->next;
            }
        }
        remember->free(remember);
        free(remember);
    }
    return changes;
   

}
void undo_changes(int board[ROWS][COLUMNS],struct Move* move,struct MSet* changes,int opponent){
    board[move->x][move->y] = E;
    struct msnode* current = changes->head;
    if(changes->size == 0){
        printf("changes size is 0 ??");
    }
    while (current != NULL)
    {
        struct Move* change = current->value;
        board[change->x][change->y] = opponent;
        current = current->next;
    }
    
}

int count_stable_discs(int board[ROWS][COLUMNS], int player) {
    bool stable[ROWS][COLUMNS] = {false};  // Keep track of stable discs
    int stable_count = 0;

    // Check  four corners 
    if (board[0][0] == player) {
        mark_stable(board, stable, player, 0, 0);
    }
    if (board[0][COLUMNS-1] == player) {
        mark_stable(board, stable, player, 0, COLUMNS-1);
    }
    if (board[ROWS-1][0] == player) {
        mark_stable(board, stable, player, ROWS-1, 0);
    }
    if (board[ROWS-1][COLUMNS-1] == player) {
        mark_stable(board, stable, player, ROWS-1, COLUMNS-1);
    }

    // Check edges
    for (int i = 1; i < COLUMNS-1; i++) {
        if (board[0][i] == player) {  // Top edge
            mark_stable(board, stable, player, 0, i);
        }
        if (board[ROWS-1][i] == player) {  // Bottom edge
            mark_stable(board, stable, player, ROWS-1, i);
        }
    }

    for (int i = 1; i < ROWS-1; i++) {
        if (board[i][0] == player) {  // Left edge
            mark_stable(board, stable, player, i, 0);
        }
        if (board[i][COLUMNS-1] == player) {  // Right edge
            mark_stable(board, stable, player, i, COLUMNS-1);
        }
    }

    // Count the stable discs
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (stable[i][j]) {
                stable_count++;
            }
        }
    }

    return stable_count;
}

void mark_stable(int board[ROWS][COLUMNS], bool stable[ROWS][COLUMNS], int player, int x, int y) {
    stable[x][y] = true;  

    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };


    for (int d = 0; d < 8; d++) {
        int dr = directions[d][0];
        int dc = directions[d][1];
        int r = x + dr;
        int c = y + dc;

        // Check bounds and if the next disc belongs to the player
        if (r >= 0 && r < ROWS && c >= 0 && c < COLUMNS && board[r][c] == player && !stable[r][c]) {
            // Recursively mark the next disc as stable if connected
            mark_stable(board, stable, player, r, c);
        }
    }
}
float evaluate_board(int board[ROWS][COLUMNS], int player) {
    int score_b = 0;  
    int score_w = 0;  
    
    // Calculate the score for both players
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (board[i][j] == B) {
                score_b++;
            } else if (board[i][j] == W) {
                score_w++;
            }
        }
    }
    
    // If the game is over, determine the winner directly
    if (is_game_over(board)) {
        if (score_b > score_w) {
            return 1.0f;   // Black wins
        } else if (score_w > score_b) {
            return -1.0f;  // White wins
        } else {
            printf("game over");
            return 0.0f;   // Draw
        }
    }

 
    int stable_b = count_stable_discs(board, B);
    int stable_w = count_stable_discs(board, W);
    
   
    struct MSet* W_possibile_moves = find_possible_moves(board,W);
    struct MSet* B_possibile_moves = find_possible_moves(board,B);
   
    int W_Nmoves = W_possibile_moves->size;
    int B_Nmoves = B_possibile_moves->size;
    
    W_possibile_moves->free(W_possibile_moves);
    B_possibile_moves->free(B_possibile_moves);
    free(W_possibile_moves);
    free(B_possibile_moves);
    int mobility_b =  B_Nmoves;
    int mobility_w =  W_Nmoves;

    // Total number of discs and stable discs
    int total_discs = score_b + score_w;
    int max_discs = ROWS * COLUMNS;

    // Normalize disc count to [-1, 1]
    float score_diff = (float)(score_b - score_w) / max_discs;

    // Normalize stable disc count to [-1, 1]
    float stable_diff = (float)(stable_b - stable_w) / max_discs;

    // Normalize mobility (available moves) to [-1, 1]
    float mobility_diff = (float)(mobility_b - mobility_w) / (ROWS * COLUMNS);

    // Weighted evaluation: disc count, stability, and mobility
    float score_weight = 0.4f;   // Disc count weight
    float stable_weight = 0.4f;  // Stable discs weight
    float mobility_weight = 0.2f; // Mobility weight

    // Final evaluation score
    float evaluation = (score_diff * score_weight) + 
                       (stable_diff * stable_weight) + 
                       (mobility_diff * mobility_weight);
    if(player == W) return -evaluation;
    else if(player == B) return evaluation;
      // Returns a value between -1 and 1
}

