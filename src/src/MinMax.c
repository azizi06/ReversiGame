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
int minimax(int board[ROWS][COLUMNS], int depth, bool maximizingPlayer, int player) ;
struct Move* best_move(int board[ROWS][COLUMNS], int player) ;
bool is_game_over(int board[ROWS][COLUMNS]);

int minimax(int board[ROWS][COLUMNS], int depth, bool maximizingPlayer, int player) {
   // printf("\nMin MAX hoooooooooooooooo\n");
    
    if (depth == 0 || is_game_over(board)) {
        return evaluate_board(board, player);  // Evaluate board when depth is 0 or game over
    }
    
    struct MSet* avaible_actions = find_possible_moves(board,player);
    struct msnode* current = avaible_actions->head;

    if (maximizingPlayer) {
        int maxEval = -10000;
       while(current != NULL){
            struct Move* action = current->value;
            struct Reversi game;
            copy_2d_array(game.game_matrix,board);
            perform_move(&game,action);
            int eval = minimax(board, depth - 1, false, -player);
            maxEval = (eval > maxEval) ? eval : maxEval;
            current= current->next;
            }
        
        return maxEval;
    } else {
        int minEval = 10000;
        while(current != NULL){
            struct Move* action = current->value;
            struct Reversi game;
            copy_2d_array(game.game_matrix,board);
            perform_move(&game,action);
            int eval = minimax(game.game_matrix, depth - 1, true, -player);
            minEval = (eval < minEval) ? eval : minEval;           
            current = current->next;
        }
        return minEval;
    }
}

// Find the best move for the AI player
struct Move* best_move(int board[ROWS][COLUMNS], int player) {
    float bestValue = -10000;
    int bestRow = -1, bestCol = -1;

    struct MSet* avaible_actions = find_possible_moves(board,player);
    //avaible_actions->print(avaible_actions);
    if(avaible_actions->size == 0){
        printf("\nNo Avaible Actions");
        return NULL;
    }
    struct msnode* current = avaible_actions->head;
     
    while(current!= NULL){
                struct Move* action = current->value;
                struct Reversi game;
                copy_2d_array(game.game_matrix,board);
                game.player = player;
                //action->print(action);
                //printf("\nai choose move :(%d,%d)",action->x,action->y);
                
                perform_move(&game,action);


                float moveValue = minimax(board, 4, false, -player);  // Depth is set to 3
                if (moveValue > bestValue) {
                    bestValue = moveValue;
                    bestRow =  action->x;
                    bestCol =  action->y;
                }
                current = current->next;
            
        }
    
    avaible_actions->free(avaible_actions);
    free(avaible_actions);
    printf("Best Move is (%d,%d)",bestRow,bestCol);
    if(bestRow == -1 || bestCol == -1){
        return NULL;
    }
    return  new_move(bestRow,bestCol);// Return the best move as a position
}

float evaluate_board(int board[ROWS][COLUMNS], int player){

    struct Reversi game;
    game.player = player;
    copy_2d_array(game.game_matrix,board);
    count_score(&game);

    if(isgame_over(&game)){
        check_winner(&game);
        if(game.winner == player){
            return 1;
        }
        else{
            return 0;
        }   
    }


    int numberOfCells = ROWS*COLUMNS;

    if(player == W){
        return  game.score_w/numberOfCells;
    }else{
        return  game.score_b/numberOfCells;
    }


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