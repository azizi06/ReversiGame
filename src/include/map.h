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
    float* (*get)( struct Map* self,int key[ROWS][COLUMNS]);

    /** 
     *  @brief  function add new node if the key not exist and update the value of the key if exists
     */
    void (*add) (struct  Map *self,int key[ROWS][COLUMNS],float value);
     /** 
     *  @brief  function to  delete existing Node
     */
    void (*del) (struct Map *self,int key[ROWS][COLUMNS]);
    void (*print) ( struct Map* self);
    /** 
     *
     *  @brief function returns float pointer or NULL if key not exists 
     */



};

/** 
     *  @brief  function to  to construct new Map 
     *  @param key a 2D int matrix
     *  @param value  a float value represents a reward
     * 
     */
struct Map *map_new();
void add_node( struct  Map *self,int key[ROWS][COLUMNS],float value);
void delete_node( struct Map *self,int key[ROWS][COLUMNS]);
void print_map( struct Map* self);
float* get_value(struct Map* self,int key[ROWS][COLUMNS]);
void free_map(struct Map* map);





#endif