
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "efuncts.h"


void *emalloc(size_t n) {
    void *p;

    p = malloc(n);
    if (p == NULL) {
        fprintf(stderr, "Malloc of %zu bytes failed\n", n);
        exit(1);
    }

    return p;
}


void ememcpy(void *p1, void *p2, size_t size) {
    if(p1 != p2) memcpy(p1, p2, size);
}

