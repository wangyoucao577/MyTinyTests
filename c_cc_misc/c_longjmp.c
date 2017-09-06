#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

void banana()
{
    printf("Enter %s\n", __func__);
    longjmp(buf, 1);
    printf("Exit %s\n", __func__);
}
int main()
{
    if (setjmp(buf)){
        printf("back in main\n");
    }else{
        printf("first time through\n");
        banana();
    }
    
    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
