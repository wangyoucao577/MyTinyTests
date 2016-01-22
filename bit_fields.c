//refer from <C Programming Language> P.150


#include <stdio.h>

struct flags_t {
	unsigned int is_keyword : 1;
	unsigned int is_extern : 1;
	unsigned int is_static : 1;
} ;

int main()
{
	printf("sizeof(struct flags_t) = %d.\n", sizeof(struct flags_t));
	return 0;	
}
