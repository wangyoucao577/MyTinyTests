#include <stdio.h>
#include <stdlib.h>

int * malloc_tranfer_pointer(int * a)
{
    a = (int*)malloc(8);
    return a;
}

int * malloc_tranfer_pointer_of_pointer(int **a)
{
    *a = (int*)malloc(8);
    return *a;
}

int main()
{
    int *p = NULL;
    int *q = NULL;

    q = malloc_tranfer_pointer(p);
    printf("p=0x%x, q=0x%x.\n", p, q);

    p = q = NULL;
    q = malloc_tranfer_pointer_of_pointer(&p);
    printf("p=0x%x, q=0x%x.\n", p, q);

    return 0;
}
/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
