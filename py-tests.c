
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "python.h"

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
    
    reversed_into(arre, container, 8, sizeof(int));
    reversed(arre, 8, sizeof(int));
    
    printf("After Rev Even\n");
    for(i = 0; i < 8; i++) printf("%d\t", arre[i]);
    printf("\n\n");
    
    printf("Container Rev\n");
    for(i = 0; i < 8; i++) printf("%d\t", container[i]);
    printf("\n\n\n");

    printf("Before Rev Odd\n");
    for(i = 0; i < 9; i++) printf("%d\t", arro[i]);
    printf("\n\n");
    
    reversed_into(arro, container, 9, sizeof(int));
    reversed(arro, 9, sizeof(int));
    
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
        
    return 0;
}

