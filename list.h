#ifndef _LIST_H_
#define _LIST_H_

typedef struct node Node;
struct node {
    // node attributes
    void *value;
    Node *next;
};


// returns length of list passed
int length(Node *);

// returns a pointer to an empty node
Node *new(void *, size_t);


// inserts value into list at index
Node *insert(Node *, void *, size_t, int i);


// inserts value to the front of the list
Node *push(Node *, void *, size_t);


// inserts value to the end of the list
Node *append(Node *, void *, size_t);


// returns node at index
Node *get(Node *, int);


// copies value at index into container, deletes node at index, and returns start of the list
Node *rem(Node *, void *, size_t, int);


// removes first node, writes data into container, and returns start of the list
Node *pop(Node *, void *, size_t);


// frees every node in the list, and the list itself: does free node values
void lfree(Node *);


// frees the passed node
void nfree(Node *);


// copies entire list, and returns a pointer to the start of the copy
Node *lcopy(Node *, size_t);


// copies passed node, and returns a pointer to a copy
Node *ncopy(Node *, size_t);


// returns the last node of a list
Node *end(Node *start);


// copies over list 2 to the end of list 1, returns node 1
Node *extend(Node *, Node *, size_t);


// reverses passed list, and returns start of reversed list
Node *lreverse(Node *, size_t);


// converts passed array to list
Node *tolist(void *, int len, size_t size);

// converts list to static array
void *toarray(Node *, size_t);


/*
soon...
void lsort(Node *, int (*compare)(void *, void *));
*/

#endif

