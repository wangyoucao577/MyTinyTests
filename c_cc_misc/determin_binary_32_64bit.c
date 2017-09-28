
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("sizeof(int) %d, sizeof(long int) %d, sizeof(void*) %d\n", sizeof(int), sizeof(long int), sizeof(void*));

    const int k64bitSize = 8 * sizeof(char);
    const int k32bitSize = 4 * sizeof(char);

    if (sizeof(void*) == k64bitSize){
        printf("This is a 64-bit binary.\n");    
    }else if (sizeof(void*) == k32bitSize){
        printf("This is a 32-bit binary.\n");    
    }else{
        printf("Unknown bit of this binary.\n");
    }

    return 0;
}
