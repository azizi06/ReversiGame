#include"solver.h"
#include "reversi.h"
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include"tools.h"
struct Solver* new_solver(float alpha,float epsilon,int player);
void update(struct Solver* self,int old_state[COLUMNS][ROWS],struct Move* action,int new_state[COLUMNS][ROWS],float reward);
void update_q_value(struct Solver* self,int old_state[COLUMNS][ROWS],struct Move* action,float old_q,float reward,float future_reward);
float best_future_reward(struct Solver* self,int state[ROWS][COLUMNS]);
struct Move* choose_move(struct Solver* self,int state[ROWS][COLUMNS]);

void update(struct Solver* self,int old_state[COLUMNS][ROWS],struct Move* action,int new_state[COLUMNS][ROWS],float reward){  
 float* old = get_value(self->q,old_state,action);
 float old_q;
 float bf_reward = 0 ;
 if(old == NULL){
    old_q = 0;
 }else{
    old_q = *old;
 }
    float best_future = best_future_reward(self,new_state);
  
    bf_reward = best_future;
    

    update_q_value(self,old_state,action,old_q,reward,bf_reward);
    

}
void update_q_value(struct Solver* self,int old_state[COLUMNS][ROWS],struct Move* action,float old_q,float reward,float future_reward){
    float new_value = old_q + (self->alpha)*((reward+future_reward)-old_q);
    add_node(self->q,old_state,action,new_value);
}
//
struct Move* choose_move2(struct Solver* self,int state[ROWS][COLUMNS]){
    struct MSet* avaible_actions = find_possible_moves(state,self->player); 
    struct msnode* current = avaible_actions->head;
    struct Move* move ;
    float* value;
    float b_value = -1;

    if(avaible_actions->size <= 0){
        return NULL;
    }
    if(choose_random(self->epsilon)){
        if(avaible_actions->size == 1){
            move = new_move((current->value)->x,(current->value)->y);
            return move;
        }
        int random;
        if(avaible_actions->size >0){
         random = (rand() % avaible_actions->size) + 1;
        }
        while(random > 1 && current != NULL ){
            current=current->next;
            random--;
        }
        if(current !=NULL){
            move = new_move((current->value)->x,(current->value)->y);
            return move;
        }
        return NULL;
    }else{
        move = new_move(0,0);
         while(current != NULL ){
            value = get_value(self->q,state,current->value);//self->q->get(self->q,state,current->value);
            if(b_value < *value){
                b_value = *value;
                move->x = (current->value)->x;
                move->y = (current->value)->y;
            }
            current=current->next;
            
        }
        return move;
    }
}
struct Move* choose_move(struct Solver* self, int state[ROWS][COLUMNS]) {
    struct MSet* avaible_actions = find_possible_moves(state, self->player);
    if (avaible_actions->size <= 0) {
        return NULL;
    }

    struct msnode* current = avaible_actions->head;
    struct Move* move = NULL;
    int x =-1;int y=-1;
    float* value;
    float b_value = -1;

    if (choose_random(self->epsilon)) {
        // Randomly select a move
        int random_index = rand() % avaible_actions->size;
        for (int i = 0; i < random_index && current != NULL; i++) {
            current = current->next;
        }
        if (current != NULL) {
            x = (current->value)->x;
            y = (current->value)->y;
        }
        printf("(random choice)");
    } else {
        // Select move with the highest Q-value
        while (current != NULL) {
            value = get_value(self->q, state, current->value);
            if (value != NULL && *value > b_value) {
                b_value = *value;
                x = (current->value)->x;
                y = (current->value)->y;
            }
            current = current->next;
        }
        if(x == -1 || y == -1){
                // Randomly select a move
            current = avaible_actions->head;
            int random_index = rand() % avaible_actions->size;
            for (int i = 0; i < random_index && current != NULL; i++) {
                current = current->next;
            }
            if (current != NULL) {
                x = (current->value)->x;
                y = (current->value)->y;
               
            }
            printf("(random choice)");
            
        }
    }
    move = new_move(x,y);
    return move;
}

float* best_future_reward2(struct Solver* self,int state[ROWS][COLUMNS]){
    struct MSet* avaible_actions = find_possible_moves(state,self->player);
    float *max_reward = NULL;
    struct msnode* current = avaible_actions->head;
    while(current != NULL){
            float* reward = get_value(self->q,state,current->value);
            if( reward != NULL && *reward >*max_reward && *reward > 0){
                *max_reward = *reward;
            }
            current=current->next;
    }
    return max_reward;
    
}
float best_future_reward(struct Solver* self, int state[ROWS][COLUMNS]) {
    struct MSet* avaible_actions = find_possible_moves(state, self->player);
    float max_reward = 0.0;
    bool found_valid_reward = false;
    struct msnode* current = avaible_actions->head;

    while (current != NULL) {
        float* reward = get_value(self->q, state, current->value);
        if (reward != NULL && *reward > max_reward && *reward > 0) {
            max_reward = *reward;
            found_valid_reward = true;
        }
        current = current->next;
    }

    // If no valid rewards were found, return 0.0
    if (!found_valid_reward) {
        return 0.0;
    }

    return max_reward;
}

struct Solver* new_solver(float alpha,float epsilon,int player){
    struct Solver* ai = (struct Solver*) malloc(sizeof(struct Solver));
    ai->alpha = alpha;
    ai->epsilon = epsilon;
    ai->player = player;
    ai->q = new_map();
    ai->move = &choose_move;
    ai->update = &update;
    return ai;
}

