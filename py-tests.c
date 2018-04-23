
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "python.h"
#include "list.h"

// TESTER
void times_two(void *value) {
    *(int *)value = *(int *)value * 2;
}

int is_even(void *value) {
    return (*(int *)value+1) % 2;
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
    n = new(&data, sizeof(double));
    
    assert(*(double *)(n->value) == data);
    assert(n->next == NULL);
    
    printf("PASSED\n\n");

    nfree(n);
}


void test_listaugment() {
    Node *n;
    double data;
    size_t size = sizeof(double);
    
    data = 0.9;
    
    n = new(&data, size);
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

    lfree(n);
}


void test_listops() {
    Node *n, *t;
    int l = 5;
    double data[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double *temp;
    size_t size = sizeof(double);
    
    printf("TESTING CONVERTERS -> ");

    n = tolist(data, l, size);
    temp = toarray(n, size);
    
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
    
    t = lcopy(n, size);
    
    assert(*(double *)(get(t, 0)->value) == 1.1);
    assert(*(double *)(get(t, 1)->value) == 2.2);
    assert(*(double *)(get(t, 2)->value) == 3.3);
    assert(*(double *)(get(t, 3)->value) == 4.4);
    assert(*(double *)(get(t, 4)->value) == 5.5);
    
    printf("PASSED\nTESTING LREVERSE   -> ");

    t = lreverse(t, size);
    
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
    
    printf("PASSED\n\n");
    
    lfree(n);
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

int main(int argc, char *argv[]) {
    test_filter_map_mM();
    test_slice_set();
    test_inters();
    test_rev();
    test_msort();
    test_list();
    
    return 0;
}

