#include <stdio.h>
#include <stdlib.h>

/*
*   参考自《Expert C Programming》1.10 “安静的改变”究竟有多安静
*   C标准在signed和unsigned执行比较或运算时，会朝着不丢失精度的方向转换。
*   由于unsigned int精度比signed int高，所以可能会出现符号数变为无符号的情况，
*   从而导致结果出错。
*
*   建议解决方案：
*   1，除非采用bit运算时，否则不使用无符号数；
    2, 涉及有符号、无符号混用时，加上强转以明确行为
*/

int array[] = {1, 2, 3, 4, 5};
#define TOTAL_ELEMENTS (sizeof(array)/sizeof(array[0]))
    
int main()
{
    int d = -1, x = 0;
    if (d <= TOTAL_ELEMENTS - 2){
        x = array[d + 1];
    }
    printf("x=%d\n", x);    /*result: x=0*/
    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
