
#include <stdio.h>
#include <stdlib.h>

int main()
{
    
    char * p = malloc(10);
    printf("p=0x%x\n", p);
    free(p);
      
    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
