#ifndef MOVESSET_H
#define MOVESSET_H

#include "Constants.h"
#include <stdbool.h>
#include "move.h"
struct msnode
{    
    struct Move *value;
    struct msnode* next;
};

struct MSet{
  struct msnode* head ;
  int size ;    
  void (*append) (struct MSet* self,struct Move *move);
  void (*del) (struct MSet* self,struct Move *move);
  void (*free) (struct MSet* self);
  void (*print)(struct MSet* self);
  bool (*exists) (struct MSet* self,struct Move *move);
};
struct MSet* new_mset();
void append_mset(struct MSet* self,struct Move *move);
void delete_msnode(struct MSet* self, struct Move *move);
void free_mset(struct MSet* self);                                          
void print_mset(struct MSet* self);
bool exists_inmset(struct MSet* self,struct Move *move);
void copy_mset(struct MSet* set1,struct MSet* set2);
#endif
