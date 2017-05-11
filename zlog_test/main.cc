
#include <stdio.h>
#include "zlog.h"

int main(){

    int rc;

    rc = zlog_init("test_hello.conf");
    if (0 != rc){
        printf("init test_hello.conf failed.\n");
        return -1;
    }

    zlog_category_t *default_cat = zlog_get_category("test_cat");
    if (!default_cat){
        zlog_fini();
        printf("zlog_get_category failed.\n");
        return -2;
    }

    zlog_info(default_cat, "hello zlog");
    zlog_info(default_cat, "line2");

    zlog_fini();

    return 0;
}

