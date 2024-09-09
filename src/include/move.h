#ifndef MOVE_H
#define MOVE_H
#include <stdbool.h>

struct Move{
    int x;
    int y;
    bool (*is_equale) (struct Move* self,struct Move* other);
    void (*print) (struct Move* self);
};

struct Move* new_move(int x,int y);
bool is_equale_move(struct Move* self,struct Move* other);
void print_move(struct Move* self);


#endif
