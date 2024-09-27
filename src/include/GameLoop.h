#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "solver.h"
void playWithAI();
void playTwoPlayerGame();
struct Solver* trainAI(int n);
void twoBotsgame();
void playWihtMinMaxAgent();
int RandomPlayerWihtMinMaxAgent(int player);
void update_ai(struct Solver *self, int old_state[COLUMNS][ROWS], struct Move *action, int new_state[COLUMNS][ROWS], float reward);

#endif