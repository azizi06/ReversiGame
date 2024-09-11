#include "moveSet.h"
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include <string.h>

// Function prototypes
struct MSet* new_mset();
void append_mset(struct MSet* self, struct Move* move);
void delete_msnode(struct MSet* self, struct Move* move);
void free_mset(struct MSet* self);
void print_mset(struct MSet* self);
bool exists_inmset(struct MSet* self, struct Move* move);
void copy_mset(struct MSet* des, struct MSet* source);

struct MSet* new_mset() {
    struct MSet* ms = (struct MSet*)malloc(sizeof(struct MSet));
    ms->head = NULL;
    ms->size = 0;
    ms->append = &append_mset;
    ms->del = &delete_msnode;
    ms->free = &free_mset;
    ms->exists = &exists_inmset;
    ms->print = &print_mset;
    return ms;
}

void append_mset(struct MSet* self, struct Move* move) {
    // Check if move already exists
    if (self->exists(self, move)) {
        return;
    }

    struct msnode* newMSNode = (struct msnode*)malloc(sizeof(struct msnode));
    newMSNode->value = new_move(move->x, move->y);
    newMSNode->next = self->head;
    self->head = newMSNode;
    self->size++;
}

void delete_msnode(struct MSet* self, struct Move* move) {
    struct msnode* current = self->head;
    struct msnode* previous = NULL;

    while (current != NULL) {
        if (is_equale_move(current->value, move)) {
            printf("Deleting move at (%d, %d)\n", current->value->x, current->value->y);

            if (previous == NULL) {
                self->head = current->next;
            } else {
                previous->next = current->next;
            }

            free(current->value); // Free the move struct
            free(current); // Free the node
            self->size--;
            return;
        }

        previous = current;
        current = current->next;
    }
}

void free_mset(struct MSet* self) {
    struct msnode* current = self->head;
    struct msnode* next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current->value); // Free the move struct
        free(current); // Free the node
        current = next_node;
    }

    self->head = NULL;
    self->size = 0;
}

void print_mset(struct MSet* self) {
    struct msnode* current = self->head;
    while (current != NULL) {
       
        print_move(current->value);
        printf("\n");
        current = current->next;
    }
    printf("\n");
}

bool exists_inmset(struct MSet* self, struct Move* move) {
    struct msnode* current = self->head;
    while (current != NULL) {
        if (is_equale_move(current->value, move)) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void copy_mset(struct MSet* des, struct MSet* source) {
    // Free existing content of destination set
    //des->free(des);

    struct msnode* sourceCurrent = source->head;
    while (sourceCurrent != NULL) {
        des->append(des, sourceCurrent->value);
        sourceCurrent = sourceCurrent->next;
    }
}
