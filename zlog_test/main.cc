
#include <stdio.h>
#ifdef _MSC_VER
#include <conio.h>
#endif
#include "zlog.h"

int main(){

    int rc;

#ifdef _MSC_VER
    char* zlog_conf_path = "../../test_hello.conf";
#else
    char* zlog_conf_path = "test_hello.conf";
#endif // _MSC_VER


    rc = zlog_init(zlog_conf_path);
    if (0 != rc){
        printf("init test_hello.conf failed.\n");
        goto End;
    }

    zlog_category_t *default_cat = zlog_get_category("test_cat");
    if (!default_cat){
        zlog_fini();
        printf("zlog_get_category failed.\n");
        goto End;
    }

    zlog_info(default_cat, "hello zlog");
    zlog_info(default_cat, "line2");

    zlog_fini();

End:
#ifdef _MSC_VER
    printf("Please press any key to continue...");
    _getch(); 
#endif
    return 0;
}

