
#include <stdio.h>
#include <stdlib.h>

void pass_char_array(char arr[])
{
	int len = sizeof(arr);
	printf("array len:%d.\n", len);
}

int main()
{
	char a[16] = {0};
	pass_char_array(a);

	return 0;
}

