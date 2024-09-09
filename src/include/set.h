#ifndef SET_H
#define SET_H
#include "Constants.h"
#include <stdbool.h>
struct snode
{    
    int  value[ROWS][COLUMNS];
    struct snode* next;
};

struct Set
{
  struct snode* head ;
  int size ;    
  void (*append) (struct Set* self,int value[ROWS][COLUMNS]);
  void (*del) (struct Set* self,int value[ROWS][COLUMNS]);
  void (*free) (struct Set* self);
  void (*print)(struct Set* self);
  bool (*exists) (struct Set* self,int value[ROWS][COLUMNS]);
};
struct Set* new_set();
void append_set(struct Set* self,int value[ROWS][COLUMNS]);
void delete_snode(struct Set* self, int value[ROWS][COLUMNS]);
void free_set(struct Set* self);
void print_set(struct Set* self);
bool exists_inset(struct Set* self,int value[ROWS][COLUMNS]);
#endif