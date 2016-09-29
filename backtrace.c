
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