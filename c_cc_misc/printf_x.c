#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x = 0x12abcFF;
	printf("%x %X %llx %llX.\n", x, x, (long long)x, (unsigned long long)x);
	return 0;
}



