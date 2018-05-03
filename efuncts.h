#ifndef _EFUNCTS_H_
#define _EFUNCTS_H_

/* wrapper for malloc
   checks if malloc returns NULL pointer, and exits if so */
void *emalloc(size_t);

/* wrapper for memcpy
   checks if copying on the same address, and does not memcpy if so
   cleans up valgrind output */
void ememcpy(void *, void *, size_t);

#endif
