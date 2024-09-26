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
struct MSet* perform_action(int game_matrix[ROWS][COLUMNS],struct Move* move,int player);
void undo_changes(int board[ROWS][COLUMNS],struct Move* move,struct MSet* changes,int opponent);

int minimax(int board[ROWS][COLUMNS], int depth, bool maximizingPlayer, int player) {
    //printf("\nMin MAX hoooooooooooooooo\n");
    
    if (depth == 0 || is_game_over(board)) {
        return evaluate_board(board, player);  // Evaluate board when depth is 0 or game over
    }
    struct MSet* avaible_actions = find_possible_moves(board,player);
    struct msnode* current = avaible_actions->head;
    if (maximizingPlayer) {
        int maxEval = -10000;
       while(current != NULL){
            struct Move* action = current->value;
            int tmp_board[ROWS][COLUMNS] = {0}; 
            copy_2d_array(tmp_board,board);
            struct MSet* changes = perform_action(board,action,player);
            int eval = minimax(board, depth - 1, false, -player);
            undo_changes(board,action,changes,-player);
            changes->free(changes);
            free(changes);
            maxEval = (eval > maxEval) ? eval : maxEval;
            current= current->next;
            }
        avaible_actions->free(avaible_actions);
        free(avaible_actions);
        return maxEval;
    } else {
        int minEval = 10000;
        while(current != NULL){
            struct Move* action = current->value;
        
            struct MSet* changes = perform_action(board,action,player);
            int eval = minimax(board, depth - 1, true, -player);
            undo_changes(board,action,changes,-player);
                changes->free(changes);
            free(changes);
            minEval = (eval < minEval) ? eval : minEval;           
            current = current->next;
        }
        avaible_actions->free(avaible_actions);
        free(avaible_actions);
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
            
                struct MSet* changes = perform_action(board,action,player);
            


                float moveValue = minimax(board, 3, false, -player);  // Depth is set to 3
                printf("Best hoooooo");
            undo_changes(board,action,changes,-player);
            changes->free(changes);
            free(changes);

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
    
    if(is_game_over(board)){
        int winner = (score_b>score_w)?B:W;
        if(winner == player){
            return 1;
        }
        else{
            return 0;
        }   
    }


    int numberOfCells = ROWS*COLUMNS;

    if(player == W){
        return  score_w/numberOfCells;
    }else{
        return  score_b/numberOfCells;
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
