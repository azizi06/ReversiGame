#include"reversi.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
struct Reversi* new_reversi();
struct Set* avaible_actions(int game_mateix[ROWS][COLUMNS]);
void perform_move(struct Reversi *self,struct Move* move);
bool isgame_over(struct Reversi *self);
void next_player(struct Reversi *self);
void count_score(struct Reversi *self);
void print_game(struct Reversi *self);


struct Reversi* new_reversi(){
    struct Reversi* r = (struct Reversi*) malloc(sizeof(struct Reversi));
    r->player = B;
    r->winner = None;
    r->score_b = 2;
    r->score_w =2;
    r->move = &perform_move;
    r->next = &next_player;
    r->isgame_over = &isgame_over;
    r->print = &print_game;
    r->count = &count_score;

    r->game_matrix[3][3]= W;
    r->game_matrix[3][4]= B;
    r->game_matrix[4][3]= B;
    r->game_matrix[4][4]= W;

    return r;
}
struct Set* avaible_actions(int game_mateix[ROWS][COLUMNS]);
void perform_move(struct Reversi *self,struct Move* move){
    self->game_matrix[move->x][move->y] = self->player;
}
bool isgame_over(struct Reversi *self){
    int number_of_cells = ROWS*COLUMNS;
    int coverd_cells = self->score_b + self->score_w;
    if(coverd_cells == number_of_cells){
        return false;
    }else if (self->score_b == 0 || self->score_w == 0)
    {
         return false;
    }
    return true;

}
void next_player(struct Reversi *self){
    self->player = (self->player == B)? W:B;
}
void count_score(struct Reversi *self){
    int score_w = 0;
    int score_b = 0;
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLUMNS;j++){
            if(self->game_matrix[i][j] == B){
                score_b++;
            }else if (self->game_matrix[i][j] == W)
            {
                score_w++;
            }
            
        }
    }
    self->score_w = score_w;
    self->score_b = score_b;
}
void print_game(struct Reversi *self){
    printf("\nGame Start...");
    printf("\nW : White player");
    printf("     B : Black player");
    printf("\nP : Possible Moves");
    printf("     # : remaining cells");
    printf("\nW : %d\nB : %d",self->score_w,self->score_b);
    printf("\n\n");
    for(int i=0;i<ROWS;i++){
        printf("\n %d  ",i);
    for(int j=0;j<COLUMNS;j++){
        int value = self->game_matrix[i][j];
        switch (value)
        {
        case W:
            printf("W ");
            break;
        case B:
            printf("B ");
            break;
        case P:
            printf("P ");
            break;
        default:
            printf("# ");
            break;
        }
    }

    }

}

