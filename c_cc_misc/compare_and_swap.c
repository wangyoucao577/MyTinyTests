#include <stdio.h>

int main()
{
    int lockval = 0;
    int oldval = __sync_val_compare_and_swap(&lockval, 0, 1);
    printf("lockval=%d.\n", lockval);

    return 0; 
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! :*/
