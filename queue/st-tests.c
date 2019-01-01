
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "../efuncts.h"



int main() {
    Stack *st;
    int i, j, k, l;
    
    i = 3;
    j = 2;
    k = 1;
    l = 0;
    
    printf("TESTING CNST -> ");
    
    st = new_stack(3);
    assert(st->cap == 3);
    assert(st->count == 0);
    
    printf("PASSED\nTESTING PUSH -> ");
    
    push_s(st, &i);
    push_s(st, &j);
    push_s(st, &k);
    push_s(st, &l);
    
    printf("PASSED\nASSERTING    -> ");
    
    assert(st->cap == 3);
    assert(st->count == 3);

    assert(*(int *)pop_s(st) == 1);
    assert(st->cap == 3);
    assert(st->count == 2);
    
    assert(*(int *)pop_s(st) == 2);
    assert(st->cap == 3);
    assert(st->count == 1);
    
    assert(*(int *)pop_s(st) == 3);
    assert(st->cap == 3);
    assert(st->count == 0);
    
    printf("PASSED\n\n");

    return 0;
}

