#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct queue Queue;
struct queue {
    void *array;
    unsigned int cap;
    unsigned int count;
    
    unsigned int curr;
    unsigned int open;
};


/* creates new static stack with the capacity of the int passed
   returns pointer to created stack*/
Stack *create_queue(unsigned int);


/* frees all malloced attributes of the passed stack */
void delete_queue(Queue *);


/* pushes pointer to stack */
void enqueue_q(queue *, void *);


/* returns top pointer on stack */
void *dequeue_q(queue *);

#endif
