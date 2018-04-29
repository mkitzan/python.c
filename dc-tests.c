
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dict.h"


void const_test() {
    Dict *dt;
    Entry *en;
    int i = 10;
    int k = 99;
    double v = 9.9;
    
    printf("TESTING CONSTR -> ");
    
    dt = new_dict(i);
    en = new_entry(&k, sizeof(int), &v);
    
    printf("PASSED\nASSERTING VALS -> ");
    
    assert(dt->cap == i);
    assert(dt->count == 0);
    
    assert(*(int *)(en->key) == 99);
    assert(en->ksize == sizeof(int));
    assert(*(double *)(en->val) == 9.9);
    
    printf("PASSED\n\n");
    
    delete_dict(dt);
    delete_entry(en);
}


void hash_test() {
    Dict *dt;
    void *val;
    int i = 7;
    
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
    
    printf("PASSED\nTESTING LOOKUP  -> ");
    
    val = lookup(dt, &k1, sizeof(k1));
    
    printf("PASSED\nASSERTING VALS  -> ");
    
    assert(*(double *)val == v1);
    printf("PASSED\n\n");
    
    delete_dict(dt);
}


int main() {
    const_test();
    hash_test();

    return 0;
}

