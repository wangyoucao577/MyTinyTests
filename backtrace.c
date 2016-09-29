
/**
  `libc`中提供的可在程序运行时获取当前堆栈信息的方法. 编译时需加上`-rdynamic`选项以导出符号至`.dynsym`符号表, 输出才能正确显示函数名.   
    `gcc -rdynamic backtrace.c`  
    `./a.out`
**/

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

void print_trace()
{
    void *frame_addresses[100] = {0};
    size_t frame_count = 0;
    
    frame_count = backtrace(frame_addresses, 100);
    printf("Obtained %zd stack frames.\n", frame_count);
    
    char **strings = backtrace_symbols(frame_addresses, frame_count);
    if (strings == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    int i;
    for (i = 0; i < frame_count; i++)
        printf("%s\n", strings[i]);
    free(strings);
}

void test1()
{
    print_trace();
}

void test2()
{
    test1();
}

int main()
{
    test2();
    return 0;
}