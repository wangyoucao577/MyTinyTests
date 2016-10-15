#include <stdio.h>
#include <stdlib.h>

int main()
{
    const int a = 10;
    int *b = &a;
    *b = 4;
    printf("a=%d.\n", a);   //result will be 4
    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
