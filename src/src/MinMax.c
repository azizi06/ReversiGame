#include<stdio.h>
#include<stdlib.h>
#include<moveSet.h>
#include "Constants.h"
#include<stdbool.h>
#include "reversi.h"
#include"tools.h"
#include"MinMax.h"
#include<string.h>

// W min Player
// B MAX Player
float evaluate_board(int board[ROWS][COLUMNS], int player);
float minimax(int board[ROWS][COLUMNS], int depth, bool maximizingPlayer, int player) ;
struct Move* best_move(int board[ROWS][COLUMNS], int player,int Depth) ;

void undo_changes(int board[ROWS][COLUMNS],struct Move* move,struct MSet* changes,int opponent);
void mark_stable(int board[ROWS][COLUMNS], bool stable[ROWS][COLUMNS], int player, int x, int y);
int count_stable_discs(int board[ROWS][COLUMNS], int player);
int Depth_Controller(int i);

struct Move* minimax_decision(int state[ROWS][COLUMNS],int player,int depth);
float min_value(int state[ROWS][COLUMNS],int player,int depth);
float max_value(int state[ROWS][COLUMNS],int player,int depth);

int Depth_Controller(int i){
    int Depth;
    if(i<20){Depth = 3;}
    else if(i<30){Depth = 3;}
    else if(i<40){Depth = 3;}
    else { Depth = 3;}

    printf("\n i : %d , Depth : %d",i,Depth);
    return Depth;
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
    if (isgame_over2(board)) {
        if (score_b > score_w) {
            return 1.0f;   // Black wins
        } else if (score_w > score_b) {
            return 1.0f;  // White wins
        } else {
            printf("\ngame over");
            return 0.0f;   // Draw
        }
    }

// 
    int stable_b = count_stable_discs(board, B);
    int stable_w = count_stable_discs(board, W);
    
   
    struct MSet* W_possibile_moves = find_possible_moves(board,W);
    struct MSet* B_possibile_moves = find_possible_moves(board,B);
   
    int W_Nmoves = W_possibile_moves->size;
    int B_Nmoves = B_possibile_moves->size;
    int mobility_b =  B_Nmoves;
    int mobility_w =  W_Nmoves;

    
    // free memory
    W_possibile_moves->free(W_possibile_moves);
    B_possibile_moves->free(B_possibile_moves);
    free(W_possibile_moves);
    free(B_possibile_moves);



    // Total number of discs and stable discs
    int total_discs = score_b + score_w;
    int max_discs = ROWS * COLUMNS;

    // Normalize disc count to [-1, 1]
    float score_diff = (float)  (ABS( score_b - score_w)) / max_discs;

    // Normalize stable disc count to [-1, 1]
    float stable_diff = (float) ABS((stable_b - stable_w)) / max_discs;

    // Normalize mobility (available moves) to [-1, 1]
    float mobility_diff = (float) ABS((mobility_b - mobility_w)) / max_discs;
   





    // Weighted evaluation: disc count, stability, and mobility
    float score_weight = 0.4f;   // Disc count weight
    float stable_weight = 0.4f;  // Stable discs weight
    float mobility_weight = 0.2f; // Mobility weight

    // Final evaluation score
    float evaluation = (score_diff * score_weight) + 
                       (stable_diff * stable_weight) + 
                       (mobility_diff * mobility_weight);
    if(player == W) return evaluation;
    else if(player == B) return evaluation;
     
}




struct Move* minimax_decision(int state[ROWS][COLUMNS],int player,int depth){
    float minmax_value = __FLT_MIN__;
    int best_x = -1;
    int best_y = -1;
    struct MSet* avaible_actions = find_possible_moves(state,player);
    struct msnode*  current = avaible_actions->head;

    while (current != NULL){
        
        struct Move* current_action = current->value;

        int state_copy[ROWS][COLUMNS];
        memcpy(state_copy, state, ROWS*COLUMNS*sizeof(int));
        perform_move2(state_copy,player,current_action);
        float action_value = min_value(state_copy,-player,depth);

        if(action_value >= minmax_value){
            best_x = current_action->x;
            best_y = current_action->y;
            minmax_value = action_value;
           // printf("\n\nminmax val %d",minmax_value);
        }
    

        current = current->next;
    }



    avaible_actions->free(avaible_actions);
    free(avaible_actions);
    if(best_x != -1 && best_y != -1){
    return new_move(best_x,best_y);
    }
    return NULL;
} 
float max_value(int state[ROWS][COLUMNS],int player,int depth){
    if(depth <= 0 || isgame_over2(state)){
        return evaluate_board(state,player);
    }
    float max_val = __FLT_MIN__;
    struct MSet* avaible_actions = find_possible_moves(state,player);
    struct msnode*  current = avaible_actions->head;

    while (current != NULL){
        struct Move* current_action = current->value;


        int state_copy[ROWS][COLUMNS];
        memcpy(state_copy, state, ROWS*COLUMNS*sizeof(int));
       
        perform_move2(state_copy,player,current_action);
        float action_value = min_value(state_copy,-player,depth-1);

        if(action_value >= max_val){
           max_val = action_value;

        }
    
        //printf("\tmax_val : %d",max_val);
        current = current->next;
    }
    

}
float min_value(int state[ROWS][COLUMNS],int player,int depth){
     if(depth <= 0 || isgame_over2(state)){
        return evaluate_board(state,player);
    }
    float min_val = __FLT_MAX__;
    struct MSet* avaible_actions = find_possible_moves(state,player);
    struct msnode*  current = avaible_actions->head;

    while (current != NULL){
        struct Move* current_action = current->value;


        int state_copy[ROWS][COLUMNS];
        memcpy(state_copy, state, ROWS*COLUMNS*sizeof(int));
        perform_move2(state_copy,player,current_action);
        float action_value = max_value(state_copy,-player,depth-1);

        if(action_value <= min_val){
           min_val = action_value;
        }
    
        //printf("\n min_val : %d",min_val);
        current = current->next;
    }
   
}
