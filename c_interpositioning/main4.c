
#include <stdio.h>

int main()
{
    char *p = "123";
    char *q = "456";
    if (0 == strcmp(p, q)){
        printf("123 is euqal to 456\n");
    }else{
        printf("123 is not equal to 456\n");
    }
      
    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
