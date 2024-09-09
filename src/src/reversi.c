#include"reversi.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
struct Reversi* new_reversi();
struct Set* avaible_actions(int game_mateix[ROWS][COLUMNS]);
void perform_move(struct Reversi *self,struct Move* move);
bool isgame_over(struct Reversi *self);
char next_player(struct Reversi *self);
int count_score(struct Reversi *self,int Player);
void print_game(struct Reversi *self);


struct Reversi* new_reversi(){
    struct Reversi* r = (struct Reversi*) malloc(sizeof(struct Reversi));
    r->player = B;
    r->winner = NULL;
    r->score_b = 2;
    r->score_w =2;
    r->move = &perform_move;
    r->next = &next_player;
    r->isgame_over = &isgame_over;
    r->print = &print_game;
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
char next_player(struct Reversi *self);
int count_score(struct Reversi *self,int Player){
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

}
void print_game(struct Reversi *self){
    printf("\nGame Start...");
    printf("\nW : White player");
    printf("\nB : Black player");
    printf("\nP : Possible Moves");
    printf("\n# : remaining cells");
    printf("\n\n\n");
    for(int i=0;i<ROWS;i++){
        printf("\n %d\t",i);
    for(int j=0;j<COLUMNS;j++){
        int value = self->game_matrix[i][j];
        switch (value)
        {
        case W:
            printf("W\t");
            break;
        case B:
            printf("B\t");
            break;
        case P:
            printf("P\t");
            break;
        default:
            printf("#\t");
            break;
        }
    }

    }

}

