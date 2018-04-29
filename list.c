
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
    
    // iterates through list while incrementing count value
    for(n = 0; start != NULL; start = start->next, n++);
    
    return n;
}


Node *end(Node *start) {
    // iterates through the list until it reaches a NULL next pointer
    for(; start->next != NULL; start = start->next);
    
    return start;
}


Node *new_node(void *val, size_t size) {
    Node *temp;
    
    // malloc the struct
    temp = (Node *)emalloc(sizeof(Node));
    // malloc the pointer
    temp->value = emalloc(size);
    
    // copy over data
    ememcpy(temp->value, val, size);
    // set default
    temp->next = NULL;
    
    return temp;
}


Node *insert(Node *start, void *val, size_t size, int i) {
    // check if index is 0, push to list and return new start if so
    if(!i) return push(start, val, size);
    
    // otherwise, get the node before, and link with new node
    link(get(start, i - 1), new_node(val, size));
    
    return start;
}


Node *push(Node *start, void *val, size_t size) {
    // make node from args
    Node *ins = new_node(val, size);
    
    // set front
    ins->next = start;
    
    return ins;
}


Node *append(Node *start, void *val, size_t size) {
    // get last node, join new node with
    end(start)->next = new_node(val, size);
    
    return start;
}


Node *get(Node *start, int i) {
    // iterates until the index value is 0
    for(; i > 0; i--) start = start->next;
    
    return start;
}


Node *rem(Node *start, void *container, size_t size, int i) {
    Node *prev, *curr;
    
    // check if index is 0, pop if so
    if(!i) return pop(start, container, size);
    
    // get node before the key index, and the next node
    prev = get(start, i - 1);
    curr = prev->next;
    // link over while retaining the key node
    prev->next = curr->next;
    
    // copy node value into container, delete node
    ememcpy(container, curr->value, size);
    delete_node(curr);
    
    return start;
}


Node *pop(Node *start, void *container, size_t size) {
    Node *temp;
    
    // retain current start
    temp = start;
    // point to its next
    start = start->next;
    
    // copy values, delete old start
    ememcpy(container, temp->value, size);
    delete_node(temp);
    
    return start;
}



void delete_node(Node *curr) {
    // free malloced value, then the struct itself
    free(curr->value);
    free(curr);
}


void delete_list(Node *start) {
    Node *prev, *curr;
    
    // iterate through list deleting previous node
    for(prev = start, curr = prev->next; curr != NULL; prev = curr, curr = curr->next) delete_node(prev);
    // fence post
    delete_node(prev);
}


Node *copy_node(Node *curr, size_t size) {
    // creates / returns reference to node made from passed node's values
    return new_node(curr->value, size);
}


Node *copy_list(Node *start, size_t size) {
    Node *temp, *curr;
    
    // copies start of list, perserves to pass back as the front
    temp = new_node(start->value, size);
    curr = temp;
    
    // co-iterates through passed list and list being built
    for(start = start->next; start != NULL; start = start->next, curr = curr->next) curr->next = copy_node(start, size);
    
    return temp;
}


Node *extend(Node *start1, Node *start2, size_t size) {
    Node *temp;
    
    // gets end of first list
    temp = end(start1);
    // grafts list2 copy to end
    temp->next = copy_list(start2, size);
    
    return start1;
}


Node *tolist(void *arr, int len, size_t size) {
    int i;
    Node *start, *end;
    
    // turns arr[0] into a start node
    start = new_node(arr, size);
    end = start;
    
    // uses len to sentinel loop, i to offset void pointer
    for(i = size, len--; len; i += size, len--) {
        // make new node from arr values, and link to end
        end->next = new_node(arr+i, size); 
        end = end->next;
    }
    
    return start;
}

void toarray(void *container, Node *start, size_t size) {
    int offset;
  
    offset = 0;
    // iterate and copy node values into array container
    for(; start != NULL; start = start->next, offset += size) ememcpy(container + offset, start->value, size);
}


Node *reverse_list(Node *start, size_t size) {
    Node *temp, *curr;
    
    // create intial node
    temp = copy_node(start, size);
    // push current node to new list, reversing list
    for(curr = start->next; curr != NULL; curr = curr->next) temp = push(temp, curr->value, size);
    // delete old list
    delete_list(start);

    return temp;
}

/*
void lsort(List *, int (*compare)(void *, void *, size_t));
*/

