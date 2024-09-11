#include "move.h"
#include <stdio.h>
#include <stdlib.h>
struct Move* new_move(int x,int y);
bool is_equale_move(struct Move* self,struct Move* other);
void print_move(struct Move* self);

struct Move* new_move(int x,int y){
    struct Move* newMove = (struct Move *)malloc(sizeof(struct Move));
    newMove->x = x;
    newMove->y = y;
    newMove->is_equale = &is_equale_move;
    return newMove;
}
bool is_equale_move(struct Move* self,struct Move* other){
    if(self->x == other->x && self->y == other->y){
        return true;
    }
    return false;
}
void print_move(struct Move* self){
    printf("Move : (%d, %d)",self->x,self->y);
}

