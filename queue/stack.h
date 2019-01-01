#ifndef _STACK_H_
#define _STACK_H_

typedef struct stack Stack;
struct stack {
    void *array;
    unsigned int cap;
    unsigned int count;
};


/* creates new static stack with the capacity of the int passed
   returns pointer to created stack*/
Stack *new_stack(unsigned int);


/* frees all malloced attributes of the passed stack */
void delete_stack(Stack *);


/* pushes pointer to stack */
void push_s(Stack *, void *);


/* returns top pointer on stack */
void *pop_s(Stack *);

#endif
