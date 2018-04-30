
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "python.h"
#include "list.h"
#include "dict.h"

#define POINTER_SIZE sizeof(void *)

void printlist(Node *n) {
    for(; n != NULL; n = n->next) printf("%f\t", *(double *)(n->value));
    printf("\n");
}

// TESTER
void times_two(void *value) {
    *(int *)value = *(int *)value * 2;
}

int is_even(void *value) {
    return (*(int *)value+1) % 2;
}

void mult_double(void *value) {
    *(double *)value = *(double *)value * 2;
}

int greater(void *value) {
    return *(double *)value < 5;
}


void test_slice_set() {
    int pats[6] = {1,1,2,2,3,3}, dups[9] = {1,6,6,3,4,4,2,0,0}, i, n;

    
    printf("Before Slice\n");
    for(i = 0; i < 6; i++) {
        printf("%d\t", pats[i]);
    }
    
    n = slice(pats, 0, 6, 2, sizeof(int));
    
    printf("\n\nAfter Slice\n");
    for(i = 0; i < n; i++) {
        printf("%d\t", pats[i]);
    }
    printf("\n\n\n");
    
    printf("Before Set\n");
    for(i = 0; i < 9; i++) {
        printf("%d\t", dups[i]);
    }
    
    n = set(dups, 9, sizeof(int));
    
    printf("\n\nAfter Set\n");
    for(i = 0; i < n; i++) {
        printf("%d\t", dups[i]);
    }
    printf("\n\n\n");
}


void test_inters() {
    int i, n, l1, l2, arr1[6]={1,2,3,4,4,1}, arr2[6]={1,9,9,8,2,3}, arr3[5]={3,3,0,1,2}, arr4[5]={3,1,4,4,0}, container[12];
    
    printf("Arrays\nA1\tA2\n");
    for(i = 0; i < 6; i++) printf("%d\t%d\n", arr1[i], arr2[i]);
    printf("\n");
    
    n = inter_arr(arr1, arr2, 6, 6, container, sizeof(int));
    
    printf("After interarr\n");
    for(i = 0; i < n; i++) printf("%d\t", container[i]);
    printf("\n\n");
    
    n = symdiff_arr(arr1, arr2, 6, 6, container, sizeof(int));
    
    printf("After diffarr\n");
    for(i = 0; i < n; i++) printf("%d\t", container[i]);
    printf("\n\n");
    
    n = inboth(arr1, arr2, 6, 6, container, sizeof(int));
    
    printf("After inboth\n");
    for(i = 0; i < n; i++) printf("%d\t", container[i]);
    printf("\n\n\n");
    
    l1 = set(arr3, 5, sizeof(int));
    l2 = set(arr4, 5, sizeof(int));
    
    printf("Sets\nS1\tS2\n");
    for(i = 0; i < 4; i++) printf("%d\t%d\n", arr3[i], arr4[i]);
    printf("\n");
    
    n = inter(arr3, arr4, l1, l2, container, sizeof(int));
    
    printf("After interset\n");
    for(i = 0; i < n; i++) printf("%d\t", container[i]);
    printf("\n\n");

    n = symdiff(arr3, arr4, l1, l2, container, sizeof(int));
    
    printf("After diffset\n");
    for(i = 0; i < n; i++) printf("%d\t", container[i]);
    printf("\n\n");
    
    n = inboth(arr3, arr4, l1, l2, container, sizeof(int));
    
    printf("After inboth\n");
    for(i = 0; i < n; i++) printf("%d\t", container[i]);
    printf("\n\n\n");
}


void test_rev() {
    int i, arre[8]={1,2,3,4,5,6,7,8}, arro[9]={0,1,2,3,4,5,6,7,8}, container[10];
    
    printf("Before Rev Even\n");
    for(i = 0; i < 8; i++) printf("%d\t", arre[i]);
    printf("\n\n");
    
    reverse_into(arre, container, 8, sizeof(int));
    reverse(arre, 8, sizeof(int));
    
    printf("After Rev Even\n");
    for(i = 0; i < 8; i++) printf("%d\t", arre[i]);
    printf("\n\n");
    
    printf("Container Rev\n");
    for(i = 0; i < 8; i++) printf("%d\t", container[i]);
    printf("\n\n\n");

    printf("Before Rev Odd\n");
    for(i = 0; i < 9; i++) printf("%d\t", arro[i]);
    printf("\n\n");
    
    reverse_into(arro, container, 9, sizeof(int));
    reverse(arro, 9, sizeof(int));
    
    printf("After Rev Odd\n");
    for(i = 0; i < 9; i++) printf("%d\t", arro[i]);
    printf("\n\n");
    
    printf("Container Rev\n");
    for(i = 0; i < 9; i++) printf("%d\t", container[i]);
    printf("\n\n\n");
}


void test_filter_map_mM() {
    void (*f)(void *);
    int (*t)(void *);
    int vals[5] = {0, 1, 2, 3, 4}, i, m, M, n;
    
    f = &times_two;
    t = &is_even;
    
    printf("Before Filter\n");
    for(i = 0; i < 5; i++) {
        printf("%d\t", vals[i]);
    }
    printf("\n");
    
    n = filter(t, vals, 5, sizeof(int));
    map(f, vals, n, sizeof(int));
    m = imin(vals, n);
    M = imax(vals, n);
    
    printf("\nAfter Filter and Map\n");
    for(i = 0; i < n; i++) {
        printf("%d\t", vals[i]);
    }
    printf("\n\nMin\tMax\n");
    
    printf("%d\t%d\n\n\n", m, M);
}


void printl(Node *start) {
    Node *temp;
    
    for(temp = start; temp->next != NULL; temp = temp->next) printf("%f\t", *(double *)temp->value);
    printf("%f\n", *(double *)temp->value);
}


void test_constructor() {
    Node *n;
    double data = 10.25;
    
    printf("\nTESTING CONSTR -> ");
    n = new_node(&data, sizeof(double));
    
    assert(*(double *)(n->value) == data);
    assert(n->next == NULL);
    
    printf("PASSED\n\n");

    delete_node(n);
}


void test_listaugment() {
    Node *n;
    double data;
    size_t size = sizeof(double);
    
    data = 0.9;
    
    n = new_node(&data, size);
    printf("INSERTING DATA   -> ");
    
    data = 1.1;
    n = insert(n, &data, size, 0);
    //[1.1, .9]
    data = 2.2;
    insert(n, &data, size, 1);
    //[1.1, 2.2, .9]
    data = 3.3;
    insert(n, &data, size, 1);
    //[1.1., 3.3, 2.2, .9]   
    data = 4.4;
    insert(n, &data, size, 3);
    //[1.1, 3.3, 2.2, 4.4, .9]
    
    printf("PASSED\nASSERTING VALUES -> ");
    
    assert(*(double *)(get(n, 0)->value) == 1.1);
    assert(*(double *)(get(n, 1)->value) == 3.3);
    assert(*(double *)(get(n, 2)->value) == 2.2);
    assert(*(double *)(get(n, 3)->value) == 4.4);
    assert(*(double *)(get(n, 4)->value) == 0.9);
    
    printf("PASSED\nPUSH APPEND DATA -> ");
    
    data = -1.1;
    n = push(n, &data, size);
    //[-1.1, 1.1, 3.3, 2.2, 4.4, .9]   
    
    data = 5.5;
    append(n, &data, size);
    //[-1.1, 1.1, 3.3, 2.2, 4.4, .9, 5.5]
    
    printf("PASSED\nASSERTING VALUES -> ");
    
    assert(*(double *)(get(n, 0)->value) == -1.1);
    assert(*(double *)(get(n, 6)->value) == 5.5);
    
    printf("PASSED\n\nTESTING POP -> ");
    
    n = pop(n, &data, size);
    assert(data == -1.1);
    //[1.1, 3.3, 2.2, 4.4, .9, 5.5]
    
    n = pop(n, &data, size);
    assert(data == 1.1);
    //[3.3, 2.2, 4.4, .9, 5.5]
    
    printf("PASSED\nASSERTING   -> ");
    
    assert(*(double *)(get(n, 0)->value) == 3.3);
    assert(*(double *)(get(n, 3)->value) == .9);
    assert(*(double *)(get(n, 4)->value) == 5.5);
    
    printf("PASSED\nTESTING REM -> ");
    
    n = rem(n, &data, size, 0);
    assert(data == 3.3);
    //[2.2, 4.4, .9, 5.5]

    n = rem(n, &data, size, 3);
    assert(data == 5.5);
    //[2.2, 4.4, .9]

    n = rem(n, &data, size, 1);
    assert(data == 4.4);
    //[2.2, .9]
    
    printf("PASSED\nASSERTING   -> ");
    
    assert(*(double *)(get(n, 1)->value) == .9);
    assert(*(double *)(get(n, 0)->value) == 2.2);
    
    printf("PASSED\n\n");

    delete_list(n);
}


void test_listops() {
    Node *n, *t;
    int l = 5;
    double data[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double *temp;
    size_t size = sizeof(double);
    
    printf("TESTING CONVERTERS -> ");
    temp = malloc(sizeof(double)*l);

    n = tolist(data, l, size);
    toarray(temp, n, size);
    
    assert(*(double *)(get(n, 0)->value) == 1.1);
    assert(*(double *)(get(n, 1)->value) == 2.2);
    assert(*(double *)(get(n, 2)->value) == 3.3);
    assert(*(double *)(get(n, 3)->value) == 4.4);
    assert(*(double *)(get(n, 4)->value) == 5.5);
   
    assert(temp[0] == 1.1);
    assert(temp[1] == 2.2);
    assert(temp[2] == 3.3);
    assert(temp[3] == 4.4);
    assert(temp[4] == 5.5);  
    
    printf("PASSED\nTESTING COPY       -> ");
    
    t = copy_list(n, size);
    
    assert(*(double *)(get(t, 0)->value) == 1.1);
    assert(*(double *)(get(t, 1)->value) == 2.2);
    assert(*(double *)(get(t, 2)->value) == 3.3);
    assert(*(double *)(get(t, 3)->value) == 4.4);
    assert(*(double *)(get(t, 4)->value) == 5.5);
    
    printf("PASSED\nTESTING REVERSE    -> ");

    t = reverse_list(t, size);
    
    assert(*(double *)(get(t, 0)->value) == 5.5);
    assert(*(double *)(get(t, 1)->value) == 4.4);
    assert(*(double *)(get(t, 2)->value) == 3.3);
    assert(*(double *)(get(t, 3)->value) == 2.2);
    assert(*(double *)(get(t, 4)->value) == 1.1);
    
    printf("PASSED\nTESTING EXTEND     -> ");
    
    extend(n, t, size);
    
    assert(*(double *)(get(n, 0)->value) == 1.1);
    assert(*(double *)(get(n, 1)->value) == 2.2);
    assert(*(double *)(get(n, 2)->value) == 3.3);
    assert(*(double *)(get(n, 3)->value) == 4.4);
    assert(*(double *)(get(n, 4)->value) == 5.5);
    assert(*(double *)(get(n, 5)->value) == 5.5);
    assert(*(double *)(get(n, 6)->value) == 4.4);
    assert(*(double *)(get(n, 7)->value) == 3.3);
    assert(*(double *)(get(n, 8)->value) == 2.2);
    assert(*(double *)(get(n, 9)->value) == 1.1);
    
    printf("PASSED\nTESTING MAP LIST   -> ");
    
    void (*funct1)(void *);
    funct1 = &mult_double;
    t = map_list(t, funct1);
    
    assert(*(double *)(get(t, 0)->value) == 11.0);
    assert(*(double *)(get(t, 1)->value) == 8.8);
    assert(*(double *)(get(t, 2)->value) == 6.6);
    assert(*(double *)(get(t, 3)->value) == 4.4);
    assert(*(double *)(get(t, 4)->value) == 2.2);
    
    printf("PASSED\nTESTING FILTER     -> ");
    
    int (*funct2)(void *);
    funct2 = &greater;
    n = filter_list(n, funct2);
    
    assert(*(double *)(get(n, 0)->value) == 1.1);
    assert(*(double *)(get(n, 1)->value) == 2.2);
    assert(*(double *)(get(n, 2)->value) == 3.3);
    assert(*(double *)(get(n, 3)->value) == 4.4);
    assert(*(double *)(get(n, 4)->value) == 4.4);
    assert(*(double *)(get(n, 5)->value) == 3.3);
    assert(*(double *)(get(n, 6)->value) == 2.2);
    assert(*(double *)(get(n, 7)->value) == 1.1);
    
    printf("PASSED\nTESTING SLICE      -> ");
    
    n = slice_list(n, sizeof(double), 1, 7, 2);
    assert(*(double *)(get(n, 0)->value) == 2.2);
    assert(*(double *)(get(n, 1)->value) == 4.4);
    assert(*(double *)(get(n, 2)->value) == 3.3);
    
    printf("PASSED\n\n");
    
    delete_list(n);
    delete_list(t);
    free(temp);
}


void test_list() {
    test_constructor();
    test_listaugment();
    test_listops();
}


void test_msort() {
    int itest[10] = {9,2,3,1,4,6,3,7,8,0}, i;
    char ctest[10] = {'q','e','a','m','i','l','p','a','z','e'};
    
    int (*f)(const void *, const void *, size_t) = &memcmp;
    
    printf("Merge Sort int arr\n");
    for(i = 0; i < 10; i++) printf("%d\t", itest[i]);
    printf("\n");
    
    msort(itest, 10, sizeof(int), f);
    
    for(i = 0; i < 10; i++) printf("%d\t", itest[i]);
    printf("\n\n\nMerge Sort char arr\n");
    
    for(i = 0; i < 10; i++) printf("%c\t", ctest[i]);
    printf("\n");
    
    msort(ctest, 10, sizeof(char), f);
    
    for(i = 0; i < 10; i++) printf("%c\t", ctest[i]);
    printf("\n");
}


void print_dict(Dict *dt) {
    unsigned int i;
    
    for(i = 0; i < dt->cap; i++) {
        if((dt->table[i]).key == NULL) printf("NULL\t");
        else printf("%c\t", *(char *)(dt->table[i]).key);
    }
        
    printf("\n%lu\n", dt->cap);
    printf("%lu\n\n", dt->count);
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


int main(int argc, char *argv[]) {
    test_filter_map_mM();
    test_slice_set();
    test_inters();
    test_rev();
    test_msort();
    test_list();
    const_test();
    hash_test();
    
    return 0;
}

