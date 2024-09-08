#include "../include/map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"tools.h"
void add_node(struct Map *self, int key[ROWS][COLUMNS], float value)
{           
    /** 
     *  @brief  function add new node if the key not exist and update the value of the key if exists
     */
         // Check if the key already exists
    struct Node *current = self->head;
    while (current != NULL) {
        if(compare_2d_array(current->key,key)){
            current->value = value;  // Update the value if key exists
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

    // Copy the key
    memcpy(newNode->key, key, sizeof(newNode->key));
    newNode->value = value;
    newNode->next = self->head;  // Insert at the head of the list
    self->head = newNode;
    self->size++;
}
void delete_node(struct Map *self, int key[ROWS][COLUMNS]){
    struct Node *curent
}
void print_map(struct Map *self){
    struct Node *current = self->head;
    printf("\n");
    while (current != NULL)
    {    
        print_matrix(current->key);      
        current = current->next;
    };
};
struct Map *map_new()
{
    struct Map *p = malloc(sizeof(struct Map));
    p->head = NULL;
    p->size = 0;
    p->add = &add_node;
    p->del = &delete_node;
    p->print = &print_map;

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