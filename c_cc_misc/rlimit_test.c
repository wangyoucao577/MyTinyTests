#define _GNU_SOURCE

#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main()
{
    struct rlimit rl;
    memset(&rl, 0, sizeof(struct rlimit));

    int ret = getrlimit(RLIMIT_NOFILE, &rl);
    if (0 != ret)
    {
        printf("getrlimit RLIMIT_NOFILE error, return %d  errno %d.\n", ret, errno);
    }
    else 
    {
        printf("getrlimit RLIMIT_NOFILE curr %d max %d.\n", rl.rlim_cur, rl.rlim_max);
    }
    return 0;
}


/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
