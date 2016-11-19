#include <stdio.h>
#include <stdlib.h>

int main()
{
    int apricot[2][3][5] = {
    	{{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}},
    	{{16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}, {26, 27, 28, 29, 30}}
    };

    int (*r)[5] = apricot[0];
    int *t = apricot[0][0];

    printf("apricot=%x\n", apricot);
    printf("r=%x, t=%x\n", r, t);
    r++;
    t++;
    printf("r++=%x, t++=%x\n", r, t);
    printf("apricot[0][1][0]=%x, apricot[0][0][1]=%x\n", &apricot[0][1][0], &apricot[0][0][1]);

    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
