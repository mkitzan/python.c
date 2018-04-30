
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dict.h"


void print_dict(Dict *dt) {
    unsigned int i;
    
    for(i = 0; i < dt->cap; i++) {
        if((dt->table[i]).key == NULL) printf("NULL\t");
        else printf("%c\t", *(char *)(dt->table[i]).key);
    }
        
    printf("\n%d\n", dt->cap);
    printf("%d\n\n", dt->count);
}


void const_test() {
    Dict *dt;
    int i = 10;
    
    printf("TESTING CONSTR -> ");
    
    dt = new_dict(i);
    
    printf("PASSED\nASSERTING VALS -> ");
    
    assert(dt->cap == i);
    assert(dt->count == 0);
    
    printf("PASSED\n\n");
    
    delete_dict(dt);
}


void hash_test() {
    Dict *dt;
    void *val1, *val2, *val3;
    unsigned int i = 7;
    
    char k1, k2, k3, k4, k5, k6, k7;
    k1 = 'k';
    k2 = 'q';
    k3 = 'e';
    k4 = 's';
    k5 = 'a';
    k6 = 'm';
    k7 = 'g';
    
    double v1, v2, v3, v4, v5, v6, v7;
    v1 = 50.1;
    v2 = 12.2;
    v3 = 34.3;
    v4 = 5.4;
    v5 = 64.5;
    v6 = 71.6;
    v7 = 91.7;
    
    
    dt = new_dict(i);
    
    printf("TESTING HASHING -> ");
    
    dt = hash(dt, &k1, sizeof(k1), &v1);
    dt = hash(dt, &k2, sizeof(k2), &v2);
    dt = hash(dt, &k3, sizeof(k3), &v3);
    dt = hash(dt, &k4, sizeof(k4), &v4);
    dt = hash(dt, &k5, sizeof(k5), &v5);
    dt = hash(dt, &k6, sizeof(k6), &v6);
    dt = hash(dt, &k7, sizeof(k7), &v7);
        
    printf("PASSED\n\n");
    
    print_dict(dt);
    print_dict(dt->old);
    
    printf("TESTING LOOKUP  -> ");
    
    val1 = lookup(dt, &k1, sizeof(k1));
    val2 = lookup(dt, &k3, sizeof(k3));
    val3 = lookup(dt, &k7, sizeof(k7));
    
    printf("PASSED\nASSERTING VALS  -> ");
    
    assert(*(double *)val1 == v1);
    assert(*(double *)val2 == v3);
    assert(*(double *)val3 == v7);
    
    printf("PASSED\nTESTING REMOVE  -> ");
    
    val1 = clear(dt, &k1, sizeof(k1));
    val2 = clear(dt, &k4, sizeof(k4));
    val3 = clear(dt, &k6, sizeof(k6));

    printf("PASSED\nASSERTING VALS  -> ");
    
    assert(*(double *)val1 == v1);
    assert(lookup(dt, &k1, sizeof(k1)) == NULL);
    assert(*(double *)val2 == v4);
    assert(lookup(dt, &k4, sizeof(k4)) == NULL);
    assert(*(double *)val3 == v6);
    assert(lookup(dt, &k6, sizeof(k6)) == NULL);
    
    printf("PASSED\n\n");
    
    print_dict(dt);
    print_dict(dt->old);
    
    delete_dict(dt);
}


int main() {
    const_test();
    hash_test();

    return 0;
}

