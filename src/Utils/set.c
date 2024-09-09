#include"set.h"
#include<stdio.h>
#include<stdlib.h>
#include "tools.h"
#include <string.h>
struct Set* new_set();
void append_set(struct Set* self,int value[ROWS][COLUMNS]);
void delete_snode(struct Set* self, int value[ROWS][COLUMNS]);
void free_set(struct Set* self);
void print_set(struct Set* self);
bool exists_inset(struct Set* self,int value[ROWS][COLUMNS]);




struct Set* new_set(){
    struct Set* s = (struct Set *)malloc(sizeof(struct Set));
    s->head = NULL;
    s->size = 0;
    s->append = &append_set;
    s->del = &delete_snode;
    s->free = &free_set;
    s->exists = &exists_inset;
    s->print = &print_set;
    s->del = &delete_snode;
}
void append_set(struct Set* self,int value[ROWS][COLUMNS]){
    struct snode* current = self->head;
    while (current != NULL){
        if(compare_2d_array(current->value,value)){
            return;
        }
        current=current->next;
    }

    struct snode* newSNode = (struct snode*)malloc(sizeof(struct snode));
    memcpy(newSNode->value, value, sizeof(newSNode->value));
    newSNode->next = self->head;
    self->head = newSNode;
    self->size++;
}
void delete_snode(struct Set* self, int value[ROWS][COLUMNS]){
    struct snode* current = self->head;
    struct snode*  pervious = self->head;
    while(current != NULL){
           if(compare_2d_array(current->value,value)){
                printf("deleting");
                pervious->next = current->next;
         
                free(current);
                return;
           }
           pervious = current;
           current = current->next;
    }
    self->size--;
}
void free_set(struct Set* self){
    struct snode* head= self->head;
    struct snode* tmp ;
    while (head != NULL)
    { 
      tmp = head;
      head = head->next;
      free(tmp->value);
      free(tmp);  
    }
    self->head = NULL;
    self->size = 0;
    
};
void print_set(struct Set* self){
    struct snode* current = self->head;
    while(current != NULL){
    printf("\n");
        print_matrix(current->value);
        current=current->next;
    }
    printf("\n");
}
bool exists_inset(struct Set* self,int value[ROWS][COLUMNS]){
    struct snode* current = self->head;
    while(current != NULL){
        if(compare_2d_array(current->value,value)){
            return true;
        }
        current = current->next;
    }
    return false;
}