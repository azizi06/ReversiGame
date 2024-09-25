#ifndef MAP_H
#define MAP_H

#include "Constants.h"
#include"reversi.h"
#include "move.h"

struct Node{
    struct Move* move;
    int state[ROWS][COLUMNS] ;
    float value;
    struct Node *next;
};
struct Map{
    struct Node *head;
    int size;
    float* (*get)( struct Map* self,int state[ROWS][COLUMNS],struct Move *move);

    /** 
     *  @brief  function add new node if the state not exist and update the value of the state if exists
     */
    void (*add) (struct  Map *self,int state[ROWS][COLUMNS],int row,int col,float value);
     /** 
     *  @brief  function to  delete existing Node
     */
    void (*del) (struct Map *self,int state[ROWS][COLUMNS],struct Move *move);
    void (*print) ( struct Map* self);
    /** 
     *
     *  @brief function returns float pointer or NULL if state not exists 
     */



};

/** 
     *  @brief  function to  to construct new Map 
     *  @param state a 2D int matrix
     *  @param value  a float value represents a reward
     * 
     */
struct Map *new_map();
void add_node( struct  Map *self,int state[ROWS][COLUMNS],int row,int col,float value);
void delete_node( struct Map *self,int state[ROWS][COLUMNS],struct Move *move);
void print_map( struct Map* self);
float* get_value(struct Map* self,int state[ROWS][COLUMNS],struct Move *move);
void free_map(struct Map* map);
struct Node* createNode(int row ,int col, int state[ROWS][COLUMNS], float value);




#endif