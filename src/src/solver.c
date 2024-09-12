#include"solver.h"
#include "reversi.h"
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
struct Solver* new_solver(float alpha,float epsilon,int player);

struct Move* choose_move(struct Solver* self,int state[ROWS][COLUMNS]);


struct Move* choose_move(struct Solver* self,int state[ROWS][COLUMNS]){
    struct MSet* avaible_actions = find_possible_moves(state,self->player); 
    struct msnode* current = avaible_actions->head;
    struct Move* move ;

    
    int random = (rand() % avaible_actions->size) + 1;
    while(random > 0 && current != NULL){
        current=current->next;
        random--;
    }
    if(current !=NULL){
        move = new_move((current->value)->x,(current->value)->y);
        return move;
    }
    return NULL;
}
struct Solver* new_solver(float alpha,float epsilon,int player){
    struct Solver* ai = (struct Solver*) malloc(sizeof(struct Solver));
    ai->alpha = alpha;
    ai->epsilon = epsilon;
    ai->player = player;
    ai->q = new_map();
    ai->move = &choose_move;
    return ai;
}

