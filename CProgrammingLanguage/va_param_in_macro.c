
#include <stdio.h>
#include <stdarg.h>

//#define my_printf(format, arg...) printf(format, arg)
#define my_printf(format, arg...) printf(format, ##arg)

int main()
{
	my_printf("test define ... : %d %f %s.\n", 3, 3.1415, (char*)__func__);
	//my_printf("test define ... with null parameters.\n", NULL);
	my_printf("test define ... with null parameters.\n");
	return 0;	
}

