
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "../efuncts.h"


Stack *new_stack(unsigned int capacity) {
    Stack *temp;
    
    temp = (Stack *)emalloc(sizeof(Stack));
    temp->array = (void **)emalloc(sizeof(void *) * capacity);
    temp->cap = capacity;
    temp->count = 0;
    
    return temp;
}


void delete_stack(Stack *st) {
    free(st->array);
    free(st);
}


void push_s(Stack *st, void *value) {
    if(st->count < st->cap) ememcpy(st->array + (st->count++ * sizeof(void *)), value, sizeof(void *));
}


void *pop_s(Stack *st) {
    if(st->count > 0) return st->array + (--st->count * sizeof(void *));
    return NULL;
}

