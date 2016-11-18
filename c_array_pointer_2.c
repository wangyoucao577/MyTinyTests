#include <stdio.h>
#include <stdlib.h>

/*
* 来自《Expert C Programming》 9.3的实验. 
*
*/

char ga[] = "abcdefg";

void pass_array(char ca[])
{
	printf("&ca=%p, &(ca[0])=%p, &(ca[1])=%p\n", &ca, &(ca[0]), &(ca[1]));
}

void pass_pionter(char *pa)
{
	printf("&pa=%p, &(pa[0])=%p, &(pa[1])=%p\n", &pa, &(pa[0]), &(pa[1]));
	printf("++pa=%p\n", ++pa);	//NOTE: 这句若是和上面在一起，那么整句就会先算++pa, 再算pa[0]和pa[1]
}

int main()
{
	pass_array(ga);
	pass_pionter(ga);

	printf("&ga=%p, &(ga[0])=%p, &(ga[1])=%p\n", &ga, &(ga[0]), &(ga[1]));
    
    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
