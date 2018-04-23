
#include <stdlib.h>
#include <stdio.h>

void *emalloc(size_t n) {
    void *p;

    p = malloc(n);
    if (p == NULL) {
        fprintf(stderr, "Malloc of %zu bytes failed\n", n);
        exit(1);
    }

    return p;
}

