#include"reversi.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <tools.h>
struct Reversi* new_reversi();
struct MSet* avaible_actions(int game_matrix[ROWS][COLUMNS],int player);
void perform_move(struct Reversi *self,struct Move* move);
void perform_move2(int state[ROWS][COLUMNS], int player, struct Move* move);
bool isgame_over(struct Reversi *self);
void next_player(struct Reversi *self);
void count_score(struct Reversi *self);
void print_game(struct Reversi *self);
bool is_valid_move(int board[ROWS][COLUMNS], int row, int col, int player);
struct MSet* find_possible_moves(int board[ROWS][COLUMNS], int player);
bool is_correct_input(struct Reversi *self,int row,int col,int player);

void check_winner(struct Reversi *self);

void check_winner(struct Reversi *self){
    self->count(self);
 if(self->score_b > self->score_w){
        self->winner = B;
        }else{
        self->winner = W;
          }
}   

struct Reversi* new_reversi(){
    struct Reversi* r = (struct Reversi*) malloc(sizeof(struct Reversi));
    //d
    r->player = B;
    r->winner = None;
    r->score_b = 2;
    r->score_w =2;
    r->move = &perform_move;
    r->next = &next_player;
    r->isgame_over = &isgame_over;
    r->print = &print_game;
    r->count = &count_score;
    //r->game_matrix = allocate_matrix(ROWS,COLUMNS);
     for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLUMNS;j++){
            r->game_matrix[i][j] = E;
        }
    } 
    //memset(r->game_matrix,0,sizeof(int[ROWS][COLUMNS]));
    int mid = ROWS /2;
    r->game_matrix[mid - 1][mid - 1]= W;
    r->game_matrix[mid-1][mid]= B;
    r->game_matrix[mid][mid-1]= B;
    r->game_matrix[mid][mid]= W;

    return r;
}

void perform_move(struct Reversi *self,struct Move* move){

    self->game_matrix[move->x][move->y] = self->player;
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };
    int opponent = (self->player == W)? B:W;
    for(int d= 0 ;d<8;d++){
        int dr = directions[d][0];
        int dc = directions[d][1];
        int r = move->x + dr;
        int c = move->y + dc;
        struct MSet* remember = new_mset();

        bool found_player = false;
        while (r<ROWS && r>=0 && c<COLUMNS && c >=0){
              if(self->game_matrix[r][c] == E){
                break;
            } 
            else if(self->game_matrix[r][c] == opponent){
                remember->append(remember,new_move(r,c));
            }else if(self->game_matrix[r][c]== self->player){
                found_player = true;
            }   
            r +=dr;
            c +=dc;        
        }
        //marking the changes :
        if(found_player){
            struct msnode* current = remember->head;
            while (current!=NULL)
            {
                struct Move* point = current->value;  
                self->game_matrix[point->x][point->y] = self->player;
                current = current->next;
            }
            
        }
        remember->free(remember);
        free(remember);
        
    }
    
   

}
//return false if game over true if not

void perform_move2(int state[ROWS][COLUMNS], int player, struct Move* move){
    // Update the game state with the player's move
    state[move->x][move->y] = player;

    // Directions for all 8 possible moves
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    int opponent = (player == W) ? B : W;

    for (int d = 0; d < 8; d++) {
        int dr = directions[d][0];
        int dc = directions[d][1];
        int r = move->x + dr;
        int c = move->y + dc;

        // Initialize a temporary list to track opponent pieces
        struct MSet* remember = new_mset();
        bool found_player = false;

        while (r < ROWS && r >= 0 && c < COLUMNS && c >= 0) {
            if (state[r][c] == E) {
                break; // Empty cell, stop checking this direction
            } else if (state[r][c] == opponent) {
                remember->append(remember, new_move(r, c)); // Store opponent piece
            } else if (state[r][c] == player) {
                found_player = true; // Found the current player's piece
                break;
            }
            r += dr;
            c += dc;
        }

        // Flip opponent pieces if a valid line was found
        if (found_player) {
            struct msnode* current = remember->head;
            while (current != NULL) {
                struct Move* point = current->value;
                state[point->x][point->y] = player; // Flip piece to current player
                current = current->next;
            }
        }

        // Free memory used for the temporary list
        remember->free(remember);
        free(remember);
    }
}
//

bool isgame_over(struct Reversi *self){
    int number_of_cells = ROWS*COLUMNS;
    int coverd_cells = self->score_b + self->score_w;
    if(coverd_cells == number_of_cells || self->score_b == 0 || self->score_w == 0){
       return true;
    }
    bool board_full = true;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            if (self->game_matrix[row][col] == 0) {
                board_full = false;
                break;
            }
        }
        if (!board_full) break;
    }
    if (board_full) return true;
    
    struct MSet* W_possibile_moves = find_possible_moves(self->game_matrix,W);
    struct MSet* B_possibile_moves = find_possible_moves(self->game_matrix,B);
   
    int W_Nmoves = W_possibile_moves->size;
    int B_Nmoves = B_possibile_moves->size;
    
    W_possibile_moves->free(W_possibile_moves);
    B_possibile_moves->free(B_possibile_moves);
    free(W_possibile_moves);
    free(B_possibile_moves);


    if(W_Nmoves == 0 && B_Nmoves == 0 ){
        return true;
    }
    
    return false;

}




bool isgame_over2(int game_matrix[ROWS][COLUMNS]){
    int number_of_cells = ROWS*COLUMNS;
    int score_b = 0;
    int score_w = 0;
    int coverd_cells = score_b + score_w;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (game_matrix[i][j] == B) score_b++;
            else if (game_matrix[i][j] == W) score_w++;
        }
    }
    
    if(coverd_cells == number_of_cells || score_b == 0 || score_w == 0){
       return true;
    }



    bool board_full = true;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            if (game_matrix[row][col] == 0) {
                board_full = false;
                break;
            }
        }
        if (!board_full) break;
    }
    if (board_full) return true;
    
    struct MSet* W_possibile_moves = find_possible_moves(game_matrix,W);
    struct MSet* B_possibile_moves = find_possible_moves(game_matrix,B);
   
    int W_Nmoves = W_possibile_moves->size;
    int B_Nmoves = B_possibile_moves->size;
    
    W_possibile_moves->free(W_possibile_moves);
    B_possibile_moves->free(B_possibile_moves);
    free(W_possibile_moves);
    free(B_possibile_moves);


    if(W_Nmoves == 0 && B_Nmoves == 0 ){
        return true;
    }
    
    return false;

}

void next_player(struct Reversi *self){
    const int next = (self->player == B)? W:B;

    struct MSet* avaible_actions = find_possible_moves(self->game_matrix,next);
    
    if(avaible_actions == NULL){
        return;
    }
    if(avaible_actions->size > 0){
        self->player = next;
    }   
    avaible_actions->free(avaible_actions);
    free(avaible_actions);
}

void count_score(struct Reversi *self){
    int score_w = 0;
    int score_b = 0;
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLUMNS;j++){
            if(self->game_matrix[i][j] == B){
                score_b++;
            }else if (self->game_matrix[i][j] == W){
                score_w++;
            }      
        }
    }
    self->score_w = score_w;
    self->score_b = score_b;

}
void print_game(struct Reversi *self){
    struct MSet* avaible_actions =  find_possible_moves(self->game_matrix, self->player);
    struct Move move;
    printf("\nW : White player");
    printf("       B : Black player");
    printf("\nP : Possible Moves");
    printf("     # : remaining cells");
    printf(ANSI_COLOR_YELLOW"\nW : %d\tB : %d\n"ANSI_RESET,self->score_w,self->score_b);
    avaible_actions->print(avaible_actions);
    printf("\n");
    printf("    ");  
    for(int i = 0;i<COLUMNS;i++){
        printf("%d ",i);
    }
    for(int i=0;i<ROWS;i++){
        printf("\n %d  ",i);
    for(int j=0;j<COLUMNS;j++){
        move.x = i;move.y=j;
        int value ;
        if(avaible_actions->exists(avaible_actions,&move)){
            value = P;
        }else{
             value = self->game_matrix[i][j];
        }
         
        switch (value)
        {
        case W:
            printf(ANSI_COLOR_RED"W "ANSI_RESET);
            break;
        case B:
            printf(ANSI_COLOR_GREEN"B "ANSI_RESET);
            break;
        case P:
            printf(ANSI_COLOR_BLUE"P "ANSI_RESET);
            break;
        default:
            printf("# ");
            break;
        }
    }

    }
    avaible_actions->free(avaible_actions);
    free(avaible_actions);

}
bool is_valid_move(int board[ROWS][COLUMNS], int row, int col, int player) {
    if (board[row][col] != 0) {
        return false; // The cell is not empty
    }

    int directions[8][2] = {
        {-1,-1}, {-1, 0},{-1,1},
        {0,-1},          {0, 1},
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

struct MSet* find_possible_moves(int board[ROWS][COLUMNS], int player) {
  
    struct MSet* possible_actions = new_mset();
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            if (is_valid_move(board, row, col, player)) {   
                struct Move* a_move = new_move(row,col);
                possible_actions->append(possible_actions,a_move);        
            }
        }
    }
    return possible_actions;
}
bool is_correct_input(struct Reversi *self,int row,int col,int player){
    if (row < 0 || row >= ROWS || col < 0 || col >= COLUMNS) {
        printf("Error: Coordinates are out of bounds \n");
        return false;
    }
    struct MSet* avaible_actions = find_possible_moves(self->game_matrix,self->player);
    struct Move move = {row,col};
    if(!avaible_actions->exists(avaible_actions,&move)){
        printf("Error: Invalid move for the current player \n");
        avaible_actions->free(avaible_actions);
        return false;
      }
    avaible_actions->free(avaible_actions);
    free(avaible_actions);
    return true;
}



void free_reversi(struct Reversi* self){
    free_matrix(self->game_matrix);
    free(self);
}
