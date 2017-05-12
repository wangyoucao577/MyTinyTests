
#include <stdio.h>
#include <assert.h>
#ifdef _MSC_VER
#include <conio.h>
#endif
#include "zlog.h"

int main(){

#ifdef _MSC_VER
    char* zlog_conf_path = "../../test_hello.conf";
#else
    char* zlog_conf_path = "test_hello.conf";
#endif // _MSC_VER

    int dzlog_ret = dzlog_init(zlog_conf_path, "default_test");
    assert(0 == dzlog_ret);

    dzlog_fatal("test dzlog fatal");
    dzlog_error("test %s", "error ");
    dzlog_warn("test log warn");
    dzlog_notice("test notice");
    dzlog_info("test info");
    dzlog_debug("test debug a");

    zlog_fini();

#ifdef _MSC_VER
    printf("Please press any key to continue...");
    _getch();
#endif

    return 0;
}

