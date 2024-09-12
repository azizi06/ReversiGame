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

};
struct Solver* new_solver(float alpha,float epsilon,int player);
void update(struct Solver* self);
void update_q_value(struct Solver* self);
float best_future_reward(struct Solver* self,int state[ROWS][COLUMNS]);
struct Move* choose_move(struct Solver* self,int state[ROWS][COLUMNS]);

#endif