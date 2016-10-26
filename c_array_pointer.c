#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a[9] = "abcdefgh";
    char *p = a;
        
    printf("&a=0x%x a=0x%x a[1]=%c\n", &a, a, a[1]);    // result: &a == a
    printf("&p=0x%x p=0x%x p[1]=%c\n", &p, p, p[1]);
    
    char *q = "abcdefgh";
    printf("q=%s\n", q);
    q[1] = 'd'; //undefine, may segmentfault, 因为C中用字符串初始化char*指针时，此字符串是常量被定义为只读，通过指针修改的话结果就是undefine的
    printf("q=%s\n", q);
        
    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
