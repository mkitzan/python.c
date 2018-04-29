
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "efuncts.h"


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


Node *new_node(void *val, size_t size) {
    Node *temp;
    
    temp = (Node *)emalloc(sizeof(Node));
    temp->value = emalloc(size);
    
    ememcpy(temp->value, val, size);
    temp->next = NULL;
    
    return temp;
}


Node *insert(Node *start, void *val, size_t size, int i) {
    if(!i) return push(start, val, size);
    
    link(get(start, i-1), new_node(val, size));
    
    return start;
}


Node *push(Node *start, void *val, size_t size) {
    Node *ins = new_node(val, size);
    
    ins->next = start;
    
    return ins;
}


Node *append(Node *start, void *val, size_t size) {
    end(start)->next = new_node(val, size);
    
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
    
    ememcpy(container, curr->value, size);
    delete_node(curr);
    
    return start;
}


Node *pop(Node *start, void *container, size_t size) {
    Node *temp;
    
    temp = start;
    start = start->next;
    
    ememcpy(container, temp->value, size);
    delete_node(temp);
    
    return start;
}



void delete_node(Node *curr) {
    free(curr->value);
    free(curr);
}


void delete_list(Node *start) {
    Node *prev, *curr;
    
    for(prev = start, curr = prev->next; curr != NULL; prev = curr, curr = curr->next) delete_node(prev);
    delete_node(prev);
}


Node *copy_node(Node *curr, size_t size) {
    return new_node(curr->value, size);
}


Node *copy_list(Node *start, size_t size) {
    Node *temp, *curr;
    
    temp = new_node(start->value, size);
    curr = temp;
    
    for(start = start->next; start != NULL; start = start->next, curr = curr->next) curr->next = copy_node(start, size);
    
    return temp;
}


Node *extend(Node *start1, Node *start2, size_t size) {
    Node *temp;
    
    temp = end(start1);
    temp->next = copy_list(start2, size);
    
    return start1;
}


Node *tolist(void *arr, int len, size_t size) {
    int i;
    Node *start, *end;
    
    start = new_node(arr, size);
    end = start;
    
    for(i = size, len--; len; i += size, len--) {
        end->next = new_node(arr+i, size); 
        end = end->next;
    }
    
    return start;
}

void toarray(void *container, Node *start, size_t size) {
    int offset;
  
    offset = 0;
    
    for(; start != NULL; start = start->next, offset += size) ememcpy(container+offset, start->value, size);
}


Node *reverse_list(Node *start, size_t size) {
    Node *temp, *curr;
    
    temp = copy_node(start, size);

    for(curr = start->next; curr != NULL; curr = curr->next) temp = push(temp, curr->value, size);

    delete_list(start);

    return temp;
}

/*
void lsort(List *, int (*compare)(void *, void *, size_t));
*/

