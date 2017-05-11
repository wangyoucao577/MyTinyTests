
#include <stdio.h>
#include <assert.h>
#include "zlog.h"

int main(){

    int dzlog_ret = dzlog_init("test_hello.conf", "default_test");
    assert(0 == dzlog_ret);

    dzlog_fatal("test dzlog fatal");
    dzlog_error("test %s", "error ");
    dzlog_warn("test log warn");
    dzlog_notice("test notice");
    dzlog_info("test info");
    dzlog_debug("test debug a");

    zlog_fini();
    return 0;
}

