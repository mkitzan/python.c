
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void printl(Node *start) {
    Node *temp;
    
    for(temp = start; temp->next != NULL; temp = temp->next) {
        printf("%f\t", *(double *)temp->value);
    }
    
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
    
    printf("PASSED\n\n");
    
    free(temp);
    delete_list(t);
    delete_list(n);
}


int main() {
    test_constructor();
    test_listaugment();
    test_listops();
    
    return 0;
}
