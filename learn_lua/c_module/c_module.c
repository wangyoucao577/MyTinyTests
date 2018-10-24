/*
    command to generate shared lib: 
    `gcc -shared -fPIC -o libc_module.so c_module.c`
*/


#include <stdio.h>

void exported_c_func1(){
    printf("这是一个C导出的函数\n");
}

