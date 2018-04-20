#ifndef _PYTHON_H_
#define _PYTHON_H_


// malloc wrapper function (tests for NULL return)
void *emalloc(size_t n);


// performs recursive merge sort on an interval of values
void sort(void *values, int low, int high, size_t size, int(*compare)(const void *, const void *, size_t size));
// wrapper for sort, does not require stating low and high index limits
void msort(void *values, int len, size_t size, int(*compare)(const void *, const void *, size_t size));


// takes an array. sorts, and removes all duplicates. returns new length of array
int set(void *values, int len, size_t size);
// takes an array of values and a container array, and transfers all unqiue values of values into container (sorted order). returns container length
int set_into(void *values, void *container, int len, size_t size);


// takes test value and array of values. returns 1 if test val in array, 0 if not
int in(void *test, void *values, int len, size_t size);


// takes two arrays and a container and joins both together (array1 + array2) into container. returns container length
int join(void *values1, void *values2, int len1, int len2, void *container, size_t size);


// performs union (join) of two arrays into container, then makes a set of the container. returns container length
int inboth(void *values1, void *values2, int len1, int len2, void *container, size_t size);


// takes two sets and container. sorts both, fills container with set1 values which do not exist in set2 (sorted order). returns contianer length
int diff(void *values1, void *values2, int len1, int len2, void *container, size_t size);
// takes two arrays and container. creates sorted sets of both, fills container with array1 values which do not exist in array2 (sorted order). returns contianer length
int diff_arr(void *values1, void *values2, int len1, int len2, void *container, size_t size);


// takes two sets and a container. sorts both, fills container with symetric difference of set1 and set2. returns container length
int symdiff(void *values1, void *values2, int len1, int len2, void *container, size_t size);
// takes two arrays and a container. fills container with symetric difference of array1 and array2. returns container length
int symdiff_arr(void *values1, void *values2, int len1, int len2, void *container, size_t size);


// takes two sets and container. sorts both, fills container (in order of set1) with intersecting values. returns length of container
int inter(void *values1, void *values2, int len1, int len2, void *container, size_t size);
// takes two arrays and container. creates sorted sets of both, fills container (in order of array1) with intersecting values. returns length of container
int inter_arr(void *values1, void *values2, int len1, int len2, void *container, size_t size);


/* takes an array, a starting index, a stopping index, and a step value. 
   slices values from start to stop (exclusive) indexing via step, and writes over the existing array (perserves order). 
   returns new length of sliced array */
int slice(void *values, int start, int stop, int step, size_t size);
/* takes an array, a container, a starting index, a stopping index, and a step value. 
   slices values from start to stop (exclusive) indexing via step, and writes into the container (perserves order). 
   returns container length */
int slice_into(void *values, void *container, int start, int stop, int step, size_t size);


// takes test function (return true or false), and array. tests each array value, removes from array all values where false. returns new length of array
int filter(int(*funct)(void *), void *values, int len, size_t size);
// takes test function (return true or false), and array. tests each array value, writes all true values into container. returns container length
int filter_into(int(*funct)(void *), void *values, void *container, int len, size_t size);


/* takes function, and array. performs function on every value in array
   function must have no return value*/
void map(void(*funct)(void *), void *values, int len, size_t size);
/* takes function, and array. perform function on every value in array, and writes result into container.
   function must return the result, so it can written into container*/ 
void map_into(void *(*funct)(void *), void *values, void *container, int len, size_t size);


// swaps values at both pointers. values must be same size
void swap(void *value1, void *value2, size_t size);


// takes an array. reverses array inplace.
void reversed(void *values, int len, size_t size);
// takes an array and container array. reverses array into container
void reversed_into(void *values, void *container, int len, size_t size);


// takes array of ints. returns smallest value
int imin(int *values, int len);
// takes array of doubles. returns smallest value
double dmin(double *values, int len);


// takes array of ints. return largest value
int imax(int *values, int len);
// takes array of doubles. returns largest value
double dmax(double *values, int len);

#endif

