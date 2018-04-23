
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "emalloc.h"


// HELPER FUNCTIONS

void link(Node *curr, Node *ins) {
    ins->next = curr->next;
    curr->next = ins;
}

// HELPER FUNCTIONS END


int length(Node *start) {
    int n;
    
    for(n = 0; start != NULL; start = start->next, n++);
    
    return n;
}


Node *end(Node *start) {
    for(; start->next != NULL; start = start->next);
    
    return start;
}


Node *new(void *val, size_t size) {
    Node *temp;
    
    temp = (Node *)emalloc(sizeof(Node));
    temp->value = emalloc(size);
    
    memcpy(temp->value, val, size);
    temp->next = NULL;
    
    return temp;
}


Node *insert(Node *start, void *val, size_t size, int i) {
    if(!i) return push(start, val, size);
    
    link(get(start, i-1), new(val, size));
    
    return start;
}


Node *push(Node *start, void *val, size_t size) {
    Node *ins = new(val, size);
    
    ins->next = start;
    
    return ins;
}


Node *append(Node *start, void *val, size_t size) {
    end(start)->next = new(val, size);
    
    return start;
}


Node *get(Node *start, int i) {
    for(; i > 0; i--) start = start->next;
    
    return start;
}


Node *rem(Node *start, void *container, size_t size, int i) {
    Node *prev, *curr;
    
    if(!i) return pop(start, container, size);
    
    prev = get(start, i-1);
    curr = prev->next;
    prev->next = curr->next;
    
    memcpy(container, curr->value, size);
    nfree(curr);
    
    return start;
}


Node *pop(Node *start, void *container, size_t size) {
    Node *temp;
    
    temp = start;
    start = start->next;
    
    memcpy(container, temp->value, size);
    nfree(temp);
    
    return start;
}



void nfree(Node *curr) {
    free(curr->value);
    free(curr);
}


void lfree(Node *start) {
    Node *prev, *curr;
    
    for(prev = start, curr = prev->next; curr != NULL; prev = curr, curr = curr->next) nfree(prev);
}


Node *ncopy(Node *curr, size_t size) {
    return new(curr->value, size);
}


Node *lcopy(Node *start, size_t size) {
    Node *temp, *curr;
    
    temp = new(start->value, size);
    curr = temp;
    
    for(start = start->next; start != NULL; start = start->next, curr = curr->next) curr->next = ncopy(start, size);
    
    return temp;
}


Node *extend(Node *start1, Node *start2, size_t size) {
    Node *temp;
    
    temp = end(start1);
    temp->next = lcopy(start2, size);
    
    return start1;
}


Node *tolist(void *arr, int len, size_t size) {
    int i;
    Node *start, *end;
    
    start = new(arr, size);
    end = start;
    
    for(i = size, len--; len; i += size, len--) {
        end->next = new(arr+i, size); 
        end = end->next;
    }
    
    return start;
}

void *toarray(Node *start, size_t size) {
    int n, offset;
    void *array;
  
    n = length(start);
    offset = 0;
    array = emalloc(n*size);
    
    for(; start != NULL; start = start->next, offset += size) memcpy(array+offset, start->value, size);
    
    return array;
}


Node *lreverse(Node *start, size_t size) {
    Node *temp, *curr;
    
    temp = ncopy(start, size);

    for(curr = start->next; curr != NULL; curr = curr->next) temp = push(temp, curr->value, size);

    lfree(start);

    return temp;
}

/*
void lsort(List *, int (*compare)(void *, void *, size_t));
*/

