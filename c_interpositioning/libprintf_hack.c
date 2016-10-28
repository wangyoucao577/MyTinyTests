#define _GNU_SOURCE 
#include <dlfcn.h>

int printf(const char* format, ...)
{
    int (*original_printf)(const char*, ...);
    original_printf = dlsym(RTLD_NEXT, "printf");

    return (*original_printf)("%s", "hacked glibc printf\n");
}


/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
