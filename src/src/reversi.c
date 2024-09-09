#include"reversi.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
struct Reversi* new_reversi(char player);
struct set* avaible_actions(int game_mateix[ROWS][COLUMNS]);
void perform_move(struct Reversi *self,struct Move* move);
bool check_winner(struct Reversi *self);
char next_player(struct Reversi *self);

struct Reversi* new_reversi(char player){
    struct Reversi* r = (struct Reversi*) malloc(sizeof(struct Reversi));
    r->player = player;
    r->winner = false; 
    r->move = &perform_move;
    r->next = &next_player;
    r->check_winner = &check_winner;
}
struct set* avaible_actions(int game_mateix[ROWS][COLUMNS]);
void perform_move(struct Reversi *self,struct Move* move){

}
bool check_winner(struct Reversi *self);
char next_player(struct Reversi *self);
