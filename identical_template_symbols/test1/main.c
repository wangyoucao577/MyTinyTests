
#include <stdio.h>
#include <stdlib.h>

void *malloc(int n) {
    printf("my malloc n=%d\n", n);
    //return malloc(n);
}

int main() {

    //int *a = malloc(sizeof(int));
    int *a = mymalloc(sizeof(int));
    *a = 10;
    printf("a = %d\n", *a);
    return 0;
}
