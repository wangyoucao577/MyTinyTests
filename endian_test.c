
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int val = 0x12345678;
    unsigned char c_val[4] = {0};
    memcpy(c_val, &val, 4);

    printf("val=0x%x, to char array-->{0x%x, 0x%x, 0x%x, 0x%x}.\n", \
        val, c_val[0], c_val[1], c_val[2], c_val[3]);

    if (c_val[0] == 0x12){
        printf("This machine is BIG ENDIAN.\n");
    }
    else if (c_val[0] == 0x78){
        printf("This machine is LITTLE ENDIAN.\n");
    }
    else
    {
        printf("This machine is UNKNOWN ENDIAN.\n");
    }
    return 0;
}


/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */

