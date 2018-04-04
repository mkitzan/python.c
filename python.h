
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


void *emalloc(size_t n);

void sort(void *values, int low, int high, size_t size, int(*compare)(const void *, const void *, size_t size));
void msort(void *values, int len, size_t size, int(*compare)(const void *, const void *, size_t size));

int set(void *values, int len, size_t size);
int set_into(void *values, void *container, int len, size_t size);


int in(void *test, void *values, int len, size_t size);


int join(void *values1, void *values2, int len1, int len2, void *container, size_t size);


int inboth(void *values1, void *values2, int len1, int len2, void *container, size_t size);


int diff(void *values1, void *values2, int len1, int len2, void *container, size_t size);
int diff_arr(void *values1, void *values2, int len1, int len2, void *container, size_t size);


int symdiff(void *values1, void *values2, int len1, int len2, void *container, size_t size);
int symdiff_arr(void *values1, void *values2, int len1, int len2, void *container, size_t size);


int inter(void *values1, void *values2, int len1, int len2, void *container, size_t size);
int inter_arr(void *values1, void *values2, int len1, int len2, void *container, size_t size);


int slice(void *values, int start, int stop, int step, size_t size);
int slice_into(void *values, void *container, int start, int stop, int step, size_t size);

int filter(int(*funct)(void *), void *values, int len, size_t size);
int filter_into(int(*funct)(void *), void *values, void *container, int len, size_t size);


void map(void(*funct)(void *), void *values, int len, size_t size);
void map_into(void *(*funct)(void *), void *values, void *container, int len, size_t size);


void swap(void *value1, void *value2, size_t size);

void reversed(void *values, int len, size_t size);
void reversed_into(void *values, void *container, int len, size_t size);


int imin(int *values, int len);
double dmin(double *values, int len)


int imax(int *values, int len);
double dmax(double *values, int len);
