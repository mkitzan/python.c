
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


void *emalloc(size_t n) {
    void *p;

    p = malloc(n);
    if (p == NULL) {
        fprintf(stderr, "malloc of %zu bytes failed", n);
        exit(1);
    }

    return p;
}


void merge(void *values, int low, int mid, int high, size_t size, int(*compare)(const void *, const void *, size_t size)) {
    void *temp;
    int lim1, lim2, i;
    
    // perform initial multiplications (so there are no other multi ops)
    low *= size;
    mid *= size;
    high *= size;
    
    // get temp array
    temp = emalloc(high-low);
    
    // copy over greater than values to their sorted position 
    for(lim1 = low, lim2 = mid, i = 0; lim1 < mid && lim2 < high; i += size) {
        if(compare(values+lim1, values+lim2, size) <= 0) {
            memcpy(temp+i, values+lim1, size);
            lim1 += size;
        } else {
            memcpy(temp+i, values+lim2, size);
            lim2 += size;
        }
    }
    
    // copy over remaining values
    memcpy(temp+i, values+lim1, mid-lim1);
    memcpy(temp+i, values+lim2, high-lim2);
    
    // copy sorted temp array into the actual array
    memcpy(values+low, temp, high-low);

    free(temp);
}


void sort(void *values, int low, int high, size_t size, int(*compare)(const void *, const void *, size_t size)) {
    int mid;
    
    if(low < high) {
        mid = (high+low) / 2;
        
        // break down into individual cells
        sort(values, low, mid++, size, compare);
        sort(values, mid, high++, size, compare);
        
        // merge up
        merge(values, low, mid, high, size, compare);
    }
}


void msort(void *values, int len, size_t size, int(*compare)(const void *, const void *, size_t size)) {
    // wrap sort fucnt
    sort(values, 0, len-1, size, compare);
}


int set(void *values, int len, size_t size) {
    void *curr, *end;
    
    // sort input
    msort(values, len, size, memcmp);
    
    // discard duplicates 
    for(curr = values+size, end = values+(len*size), len = size; curr < end; curr += size) {
        if(memcmp(curr-size, curr, size)) {
            memcpy(values+len, curr, size);
            len += size;
        }       
    }
    
    // return new length of array
    return len / size;
}


int set_into(void *values, void *container, int len, size_t size) {
    void *end;
    
    // sort input
    msort(values, len, size, memcmp);
    
    // discard duplicates
    memcpy(container, values, size);
    for(end = values+(len*size), len = size, values += size; values < end; values += size) {
        if(memcmp(values-size, values, size)) {
            memcpy(container+len, values, size);
            len += size;
        }
    }
    
    // return new length of array
    return len / size;
}


int in(void *test, void *values, int len, size_t size) {
    void *end;
    
    // check if any values match the test value
    for(end = values+(len*size); values < end; values += size) if(!memcmp(test, values, size)) return 1;
    
    return 0;
}


int join(void *values1, void *values2, int len1, int len2, void *container, size_t size) {
    // copies first array into container
    memcpy(container, values1, len1*size);
    // copies second array into container
    memcpy(container+(len1*size), values2, len2*size);
    
    return len1+len2;
}


int inboth(void *values1, void *values2, int len1, int len2, void *container, size_t size) {
    // join both arrays
    int n = join(values1, values2, len1, len2, container, size);
    
    // return the set of elements
    return set(container, n, size);
}


int diff(void *values1, void *values2, int len1, int len2, void *container, size_t size) {
    void *end;
    int n;
    
    // checks for each element of A1 if not in A2
    for(n = 0, end = values1+(len1*size); values1 < end; values1 += size) {
        if(!in(values1, values2, len2, size)) {
            memcpy(container+n, values1, size);
            n += size;
        }
    }
    
    return n / size;
}


int diff_arr(void *values1, void *values2, int len1, int len2, void *container, size_t size) {
    void *vals1, *vals2, *end;
    int n;
    
    // create the temp arrays, so existing arrays aren't destroyed
    vals1 = emalloc(len1*size);
    vals2 = emalloc(len2*size);

    // create sets of input arrays
    len1 = set_into(values1, vals1, len1, size);
    len2 = set_into(values2, vals2, len2, size);
    
    // check for each element of A1 not in A2
    for(n = 0, end = vals1+(len1*size); vals1 < end; vals1 += size) {
        if(!in(vals1, vals2, len2, size)) {
            memcpy(container+n, vals1, size);
            n += size;
        }
    }
    
    free(vals1);
    free(vals2);
    
    return n / size;
}


int symdiff(void *values1, void *values2, int len1, int len2, void *container, size_t size) {
    void *end, *curr;
    int n;
    
    for(n = 0, curr = values1, end = values1+(len1*size); curr < end; curr += size) {
        if(!in(curr, values2, len2, size)) {
            memcpy(container+n, curr, size);
            n += size;
        }
    }
    
    for(curr = values2, end = values2+(len2*size); curr < end; curr += size) {
        if(!in(curr, values1, len1, size)) {
            memcpy(container+n, curr, size);
            n += size;
        }
    }
    
    return n / size;
}


int symdiff_arr(void *values1, void *values2, int len1, int len2, void *container, size_t size) {
    void *vals1, *vals2, *curr, *end;
    int n;
    
    vals1 = emalloc(len1*size);
    vals2 = emalloc(len2*size);

    len1 = set_into(values1, vals1, len1, size);
    len2 = set_into(values2, vals2, len2, size);
    
    for(n = 0, curr = vals1, end = vals1+(len1*size); curr < end; curr += size) {
        if(!in(curr, vals2, len2, size)) {
            memcpy(container+n, curr, size);
            n += size;
        }
    }
    
    for(curr = vals2, end = vals2+(len2*size); curr < end; curr += size) {
        if(!in(curr, vals1, len1, size)) {
            memcpy(container+n, curr, size);
            n += size;
        }
    }
    
    free(vals1);
    free(vals2);
    
    return n / size;
}


int inter(void *values1, void *values2, int len1, int len2, void *container, size_t size) {
    void *end;
    int n;
    
    // checks if each element in A1 is in A2
    for(n = 0, end = values1+(len1*size); values1 < end; values1 += size) {
        if(in(values1, values2, len2, size)) {
            memcpy(container+n, values1, size);
            n += size;
        }
    }
    
    return n / size;
}


int inter_arr(void *values1, void *values2, int len1, int len2, void *container, size_t size) {
    void *vals1, *vals2, *curr, *end;
    int n;
    
    // create temp arrays
    vals1 = emalloc(len1*size);
    vals2 = emalloc(len2*size);

    // create set of input arrays
    len1 = set_into(values1, vals1, len1, size);
    len2 = set_into(values2, vals2, len2, size);
    
    // checks if each element in A1 is in A2   
    for(n = 0, curr = vals1, end = vals1+(len1*size);  curr < end; curr += size) {
        if(in(curr, vals2, len2, size)) {
            memcpy(container+n, curr, size);
            n += size;
        }
    }
    
    free(vals1);
    free(vals2);
    
    return n / size;
}


int slice(void *values, int start, int stop, int step, size_t size) {
    int n;
    start *= size;
    stop *= size;
    step *= size;
    
    // copies each value from the array that the slice hits
    for(n = 0; start < stop; start += step, n += size) memcpy(values, values+start, size);
    
    //returns length of new array
    return n / size;
}


int slice_into(void *values, void *container, int start, int stop, int step, size_t size) {
    int n;
    start *= size;
    stop *= size;
    step *= size;
    
    // copies each value from the array that the slice hits
    for(n = 0; start < stop; start += step, n += size) memcpy(container+n, values+start, size);
    
    //returns length of new array
    return n / size;
}


int filter(int(*funct)(void *), void *values, int len, size_t size) {
    void *curr, *end;
    
    // test each value: if true, copy into the filtered list
    for(curr = values, end = values+(len*size), len = 0; curr < end; curr += size) {
        if(funct(curr)) {
            memcpy(values+len, curr, size);
            len += size;
        }
    }
    
    // returns new length of array
    return len / size;
}

int filter_into(int(*funct)(void *), void *values, void *container, int len, size_t size) {
    void *end;
    
    // test each value: if true, copy into the container
    for(len = 0, end = values+(len*size); values < end; values += size) {
        if(funct(values)) {
            memcpy(container+len, values, size);
            len += size;
        }
    }
    
    // returns length of container
    return len / size;
}


void map(void(*funct)(void *), void *values, int len, size_t size) {
    void *end;
    
    // perform function on each value in array
    for(end = values+(len*size); values < end; values += size) funct(values);
}


void map_into(void *(*funct)(void *), void *values, void *container, int len, size_t size) {
    void *end;
    
    // copy result of function into the container
    for(end = values+(len*size); values < end; values += size, container += size) memcpy(container, funct(values), size);
}


void swap(void *value1, void *value2, size_t size) {
    void *temp = emalloc(size);
    
    memcpy(temp, value1, size);
    memcpy(value1, value2, size);
    memcpy(value2, temp, size);
    
    free(temp);
}


void reversed(void *values, int len, size_t size) {
    int i, lim;
    
    for(i = 0, lim = (len--/2)*size, len *= size; i < lim; i += size) swap(values+i, values+(len-i), size);
}


void reversed_into(void *values, void *container, int len, size_t size) {
    void *end;
    
    for(end = values+(--len*size), len = 0; end >= values; end -= size, len += size) memcpy(container+len, end, size);
}


int min_i(int *values, int len) {
    int i, min;
    
    for(i = 1, min = *values; i < len; i++) if(values[i] < min) min = values[i];
    
    return min;
}


double min_d(double *values, int len) {
    int i;
    double min;
    
    for(i = 1, min = *values; i < len; i++) if(values[i] < min) min = values[i];
    
    return min;
}


int max_i(int *values, int len) {
    int i, max;
    
    for(i = 1, max = *values; i < len; i++) if(values[i] > max) max = values[i];
    
    return max;
}


double max_d(double *values, int len) {
    int i;
    double max;
    
    for(i = 1, max = *values; i < len; i++) if(values[i] > max) max = values[i];
    
    return max;
}


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
    m = min_i(vals, n);
    M = max_i(vals, n);
    
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

