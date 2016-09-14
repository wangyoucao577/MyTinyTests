#include <stdio.h>

void main()
{
    int cnt = 0;
    char line[1024];

    /*
 *  We have explicitly set line buffering since the stdio routines
 *  will not see the socket as a terminal device.
 *  */

    setvbuf(stdout, NULL, _IOLBF, 0);
    while(fgets(line, sizeof(line), stdin) != NULL)
        printf("%3i: %s", ++cnt, line);

}


/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
