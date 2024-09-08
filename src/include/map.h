#ifndef MAP_H
#define MAP_H

#include "Constants.h"
struct Node{
    int key[ROWS][COLUMNS] ;
    float value;
    struct Node *next;
};
struct Map{
    struct Node *head;
    int size;
    //functions 
    void (*add) (struct  Map *self,int key[ROWS][COLUMNS],float value);
    void (*del) (struct Map *self,int key[ROWS][COLUMNS]);
    void (*print) ( struct Map* self);


};
struct Map *map_new();
void add_node( struct  Map *self,int key[ROWS][COLUMNS],float value);
void delete_node( struct Map *self,int key[ROWS][COLUMNS]);
void print_map( struct Map* self);
void free_map(struct Map* map);





#endif