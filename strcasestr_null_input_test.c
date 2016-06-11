
#include <stdio.h>

int main()
{
    char * str = strcasestr(NULL, ",");
    printf("str:0x%x.\n", str);

    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */

