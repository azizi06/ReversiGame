#include"solver.h"
#include "reversi.h"
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
struct Solver* new_solver(float alpha,float epsilon,int player);
void update(struct Solver* self,int old_state[COLUMNS][ROWS],struct Move* action,int new_state[COLUMNS][ROWS],float reward);
void update_q_value(struct Solver* self,int old_state[COLUMNS][ROWS],struct Move* action,float old_q,float reward,float future_reward);
float best_future_reward(struct Solver* self,int state[ROWS][COLUMNS]);
struct Move* choose_move(struct Solver* self,int state[ROWS][COLUMNS]);

void update(struct Solver* self,int old_state[COLUMNS][ROWS],struct Move* action,int new_state[COLUMNS][ROWS],float reward){  
 float* old = get_value(self->q,old_state,action);
 float old_q;
 if(old == NULL){
    old_q = 0;
 }else{
    old_q = *old;
 }
    float best_future = best_future_reward(self,new_state);
    update_q_value(self,old_state,action,old_q,reward,best_future);

}
void update_q_value(struct Solver* self,int old_state[COLUMNS][ROWS],struct Move* action,float old_q,float reward,float future_reward){
    float new_value = old_q + (self->alpha)*((reward+future_reward)-old_q);
    add_node(self->q,old_state,action,new_value);
}
//
struct Move* choose_move(struct Solver* self,int state[ROWS][COLUMNS]){
    struct MSet* avaible_actions = find_possible_moves(state,self->player); 
    struct msnode* current = avaible_actions->head;
    struct Move* move ;
    if(avaible_actions->size == 1){
        move = new_move((current->value)->x,(current->value)->y);
        return move;
    }
    
    int random = (rand() % avaible_actions->size) + 1;
    printf("random : %d ",random);
    while(random > 1 && current != NULL ){
        current=current->next;
        random--;
    }
    if(current !=NULL){
        move = new_move((current->value)->x,(current->value)->y);
        return move;
    }
    return NULL;
}

float best_future_reward(struct Solver* self,int state[ROWS][COLUMNS]){
    struct MSet* avaible_actions = find_possible_moves(state,self->player);
    float *max_reward = NULL;
    struct msnode* current = avaible_actions->head;
    while(current != NULL){
            float* reward = get_value(self->q,state,current->value);
            if( reward != NULL && *reward >*max_reward && *reward > 0){
                *max_reward = *reward;
            }
    }
    if(max_reward == NULL){
        return 0;
    }
    return *max_reward;
    
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

