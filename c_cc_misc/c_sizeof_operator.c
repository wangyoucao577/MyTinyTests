#include <stdio.h>
#include <stdlib.h>

int main()
{
    int * p = NULL;
    
    //sizeof是一个操作符，参数为变量时可以不用加括号
    //所以这句里面是sizeof(*p)的意思
    //这个风格不建议使用
    int q = 10 * sizeof * p;    
    
    //sizeof在操作类型时，必须加括号
    int r = 10 * sizeof(int);
    
    printf("q=%d, r=%d\n", q, r);
    
    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
