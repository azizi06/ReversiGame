#include "../include/map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"tools.h"
struct Map *new_map();
void add_node( struct  Map *self,int state[ROWS][COLUMNS],struct Move *move,float value);
void delete_node( struct Map *self,int state[ROWS][COLUMNS],struct Move *move);
void print_map( struct Map* self);
float* get_value(struct Map* self,int state[ROWS][COLUMNS],struct Move *move);
void free_map(struct Map* map);

void add_node(struct Map *self, int state[ROWS][COLUMNS],struct Move *move, float value)
{           
    /** 
     *  @brief  function add new node if the state not exist and update the value of the state if exists
     */
         // Check if the state already exists
    struct Node *current = self->head;
    while (current != NULL) {
        if(compare_2d_array(current->state,state) && is_equale_move(current->move,move)){
            current->value = value;  // Update the value if state exists
   
            return;

        }
       
        current = current->next;
    }

    // Key not found, insert a new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->move = new_move(move->x,move->y);

    // Copy the state
    memcpy(newNode->state, state, sizeof(newNode->state));
    newNode->value = value;
    newNode->next = self->head;  // Insert at the head of the list
    self->head = newNode;
    self->size++;


}
void delete_node(struct Map *self, int state[ROWS][COLUMNS],struct Move *move){
    struct Node *current = self->head;
    struct Node  *previous = NULL;

     while ((current != NULL) )
     {
      if(compare_2d_array(current->state,state) && is_equale_move(current->move,move)){
        if (previous == NULL)
        {
            self->head = current->next;
        }else{
            previous->next = current->next;
        }
        
        
        
     
        free(current);
        return; 
      }
       previous =current;
       current = current->next;
      
     }
     
    
}
void print_map(struct Map *self){
    struct Node *current = self->head;

    printf("\n");
    while (current != NULL)
    { 
        print_move(current->move);
        print_matrix(current->state);      
        printf("\nvalue  : %f",current->value);
        printf("-------------------------");
        current = current->next;
    };
};
float* get_value(struct Map* self,int state[ROWS][COLUMNS],struct Move *move){
    struct Node* current = self->head;
    while(current != NULL){
        
        if(compare_2d_array(current->state,state) && is_equale_move(current->move,move)){
           
            return &(current->value);
        }
        current = current->next;
    }
    return NULL;

}
struct Map *new_map()
{
    struct Map *p = malloc(sizeof(struct Map));
    p->head = NULL;
    p->size = 0;
    p->add = &add_node;
    p->del = &delete_node;
    p->print = &print_map;
    p->get = &get_value;

    return p;
}
void free_map(struct Map *map) {
    struct Node *current = map->head;
    while (current != NULL) {
        struct Node *next = current->next;
     
        free(current);
        current = next;
    }
    map->head = NULL;
    map->size = 0;
}