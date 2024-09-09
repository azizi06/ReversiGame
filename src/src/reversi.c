#include"reversi.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
struct Reversi* new_reversi(char player);
struct set* avaible_actions(int game_mateix[ROWS][COLUMNS]);
void perform_move(struct Move* move);
bool check_winner(int game_matrix[ROWS][COLUMNS]);
char next_player(int gamme_matrix[ROWS][COLUMNS]);

struct Reversi* new_reversi(char player){
    struct Reversi* r = (struct Reversi*) malloc(sizeof(struct Reversi));
    r->player = player;
    r->move = &perform_move;
    r->winner = false; 
}
struct set* avaible_actions(int game_mateix[ROWS][COLUMNS]);
void perform_move(struct Move* move);
bool check_winner(int game_matrix[ROWS][COLUMNS]);
char next_player(int gamme_matrix[ROWS][COLUMNS]);
