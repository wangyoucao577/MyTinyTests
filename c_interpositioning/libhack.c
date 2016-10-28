#include <stdio.h>

void *malloc(size_t size)
{
    printf("hack malloc, size %d\n", (int)size);
    return NULL;
}

void free(void *ptr)
{
    printf("hack free\n");
}


/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
