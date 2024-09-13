#ifndef SOLVER_H
#define SOLVER_H
#include "map.h"
struct Solver{
    // learning rate :
    float alpha; 
    // random move choosing rate
    float epsilon;
    struct Map* q;
    int player;
    struct Move* (*move) (struct Solver* self,int state[ROWS][COLUMNS]);
    void (*update) (struct Solver* self,int old_state[COLUMNS][ROWS],struct Move* action,int new_state[COLUMNS][ROWS],float reward);

};
struct Solver* new_solver(float alpha,float epsilon,int player);
void update(struct Solver* self,int old_state[COLUMNS][ROWS],struct Move* action,int new_state[COLUMNS][ROWS],float reward);
void update_q_value(struct Solver* self,int old_state[COLUMNS][ROWS],struct Move* action,float old_q,float reward,float future_reward);
float best_future_reward(struct Solver* self,int state[ROWS][COLUMNS]);
struct Move* choose_move(struct Solver* self,int state[ROWS][COLUMNS]);

#endif