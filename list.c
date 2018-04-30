
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

// HELPER FUNCTIONS tail


int length(Node *head) {
    int n;
    
    // iterates through list while incrementing count value
    for(n = 0; head != NULL; head = head->next, n++);
    
    return n;
}


Node *end(Node *head) {
    // iterates through the list until it reaches a NULL next pointer
    for(; head->next != NULL; head = head->next);
    
    return head;
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


Node *insert(Node *head, void *val, size_t size, int i) {
    // check if index is 0, push to list and return new head if so
    if(!i) return push(head, val, size);
    
    // otherwise, get the node before, and link with new node
    link(get(head, i-1), new_node(val, size));
    
    return head;
}


Node *push(Node *head, void *val, size_t size) {
    // make node from args
    Node *ins = new_node(val, size);
    
    // set front
    ins->next = head;
    
    return ins;
}


Node *append(Node *head, void *val, size_t size) {
    // get last node, join new node with
    end(head)->next = new_node(val, size);
    
    return head;
}


Node *get(Node *head, int i) {
    // iterates until the index value is 0
    for(; i > 0; i--) head = head->next;
    
    return head;
}


Node *rem(Node *head, void *container, size_t size, int i) {
    Node *prev, *curr;
    
    // check if index is 0, pop if so
    if(!i) return pop(head, container, size);
    
    // get node before the key index, and the next node
    prev = get(head, i-1);
    curr = prev->next;
    // link over while retaining the key node
    prev->next = curr->next;
    
    // copy node value into container, delete node
    ememcpy(container, curr->value, size);
    delete_node(curr);
    
    return head;
}


Node *pop(Node *head, void *container, size_t size) {
    Node *temp;
    
    // retain current head
    temp = head;
    // point to its next
    head = head->next;
    
    // copy values, delete old head
    ememcpy(container, temp->value, size);
    delete_node(temp);
    
    return head;
}



void delete_node(Node *curr) {
    // free malloced value, then the struct itself
    free(curr->value);
    free(curr);
}


void delete_list(Node *head) {
    Node *prev, *curr;
    
    // iterate through list deleting previous node
    for(prev = head, curr = prev->next; curr != NULL; prev = curr, curr = curr->next) delete_node(prev);
    // fence post
    delete_node(prev);
}


Node *copy_node(Node *curr, size_t size) {
    // creates / returns reference to node made from passed node's values
    return new_node(curr->value, size);
}


Node *copy_list(Node *head, size_t size) {
    Node *temp, *curr;
    
    // copies head of list, perserves to pass back as the front
    temp = new_node(head->value, size);
    curr = temp;
    
    // co-iterates through passed list and list being built
    for(head = head->next; head != NULL; head = head->next, curr = curr->next) curr->next = copy_node(head, size);
    
    return temp;
}


Node *extend(Node *head1, Node *head2, size_t size) {
    Node *temp;
    
    // gets tail of first list
    temp = end(head1);
    // grafts list2 copy to tail
    temp->next = copy_list(head2, size);
    
    return head1;
}


Node *tolist(void *arr, int len, size_t size) {
    int i;
    Node *head, *tail;
    
    // turns arr[0] into a head node
    head = new_node(arr, size);
    tail = head;
    
    // uses len to sentinel loop, i to offset void pointer
    for(i = size, len--; len; i += size, len--) {
        // make new node from arr values, and link to tail
        tail->next = new_node(arr+i, size); 
        tail = tail->next;
    }
    
    return head;
}

void toarray(void *container, Node *head, size_t size) {
    int offset;
  
    offset = 0;
    // iterate and copy node values into array container
    for(; head != NULL; head = head->next, offset += size) ememcpy(container+offset, head->value, size);
}


Node *reverse_list(Node *head, size_t size) {
    Node *temp, *curr;
    
    // create intial node
    temp = copy_node(head, size);
    // push current node to new list, reversing list
    for(curr = head->next; curr != NULL; curr = curr->next) temp = push(temp, curr->value, size);
    // delete old list
    delete_list(head);

    return temp;
}


Node *filter_list(Node *head, int (*funct)(void *)) {
    Node *prev, *curr;
    
    // iterate through list, test each node
    for(prev = NULL, curr = head; curr != NULL;) {
        if(!funct(curr->value)) {
            if(prev == NULL) {
                // case if node is head
                prev = curr;
                curr = curr->next;
                delete_node(prev);
                prev = NULL;
                head = curr;
            } else {
                // default case (mid or tail node)
                prev->next = curr->next;
                delete_node(curr);
                curr = prev->next;
            }
        } else {
            // move on if value passes
            prev = curr;
            curr = curr->next;
        }
    }
    
    // must return head incase head node was filtered out
    return head;
}


Node *map_list(Node *head, void (*funct)(void *)) {
    Node *curr;
    
    // iterate and perform function on every node
    for(curr = head; curr != NULL; curr = curr->next) funct(curr->value);
    
    // trying to perserve a return format
    return head;
}


Node *slice_list(Node *head, size_t size, int start, int stop, int step) {
    int i;
    Node *temp, *new, *curr;
    
    // vet those input
    if(stop <= start) return head;
    
    // get the node to start at, and copy it to the new list
    curr = get(head, start);
    temp = copy_node(curr, size);
    new = temp;
    
    for(i = 1, curr = curr->next; i < (stop - start) && curr != NULL; i++, curr = curr->next) {
        // copy node if it's position lands within the step
        if(!(i % step)) {
            temp->next = copy_node(curr, size);
            temp = temp->next;
        }
    }

    // free previous list
    delete_list(head);

    return new;
}


/*
void lsort(List *, int (*compare)(void *, void *, size_t));
*/

