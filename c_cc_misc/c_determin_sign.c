#include <stdio.h>

#define IDENTIFIER_TO_STRING(value) (#value)
#define TYPICAL_VALUE_OF_TYPE(type) ((type)1)


// NOTE: 方法1
//	1, can not determin short/unsigned short/char/unsigned char, because they'll automatically convert to int/unsigned int in expressions
#define IS_VALUE_UNSIGNED(x) ( ((x) >= 0) && ((~x) >= 0) )
#define IS_VALUE_UNSIGNED_TO_STRING(x) ((IS_VALUE_UNSIGNED(x) ? "unsigned" : "signed"))

#define PRINT_VALUE_TYPE(value) (printf("\'%s\' is %s\n", IDENTIFIER_TO_STRING(value), IS_VALUE_UNSIGNED_TO_STRING(value)))
#define PRINT_TYPE_TYPE(type) (printf("\'%s\' is %s\n", IDENTIFIER_TO_STRING(type), IS_VALUE_UNSIGNED_TO_STRING(TYPICAL_VALUE_OF_TYPE(type))))

// NOTE: 方法2
//	1, also can not determin short/unsigned short/char/unsigned char
#define IS_TYPE_UNSIGNED_2(type) ((type)0 - 1 > 0)
#define IS_TYPE_UNSIGNED_TO_STRING_2(type) ((IS_TYPE_UNSIGNED_2(type) ? "unsigned" : "signed"))

#define PRINT_TYPE_TYPE_2(type) (printf("\'%s\' is %s\n", IDENTIFIER_TO_STRING(type), IS_TYPE_UNSIGNED_TO_STRING_2(type)))

// NOTE: 方法3
//	1, define a new variable with macro because constant cannot '|='
// #define IS_VALUE_UNSIGNED_3(x)	(((x) |= (((typeof(x))0x1) << (sizeof(x) * 8 - 1))) > 0 ? 1 : 0)
#define IS_VALUE_UNSIGNED_3(x)	({ \
	typeof(x) y = x; \
	((y) |= (((typeof(x))0x1) << (sizeof(x) * 8 - 1))) > 0 ? 1 : 0;\
})

#define IS_VALUE_UNSIGNED_TO_STRING_3(x) (IS_VALUE_UNSIGNED_3(x) ? "unsigned" : "signed")
#define PRINT_VALUE_TYPE_3(value) (printf("\'%s\' is %s\n", IDENTIFIER_TO_STRING(value), IS_VALUE_UNSIGNED_TO_STRING_3(value)))
#define PRINT_TYPE_TYPE_3(type) (printf("\'%s\' is %s\n", IDENTIFIER_TO_STRING(type), IS_VALUE_UNSIGNED_TO_STRING_3(TYPICAL_VALUE_OF_TYPE(type))))


int main()
{
	char c = 10;
	unsigned char uc = 10;
	short s = 10;
	unsigned short us = 10;
	int i = 10;
	unsigned int ui = 10;
	long l = 10L;
	unsigned long ul = 10L;
	long long ll = 10LL;
	unsigned long long ull = 10LL;

	int i_zero = 0;
	unsigned int ui_zero = 0;

	printf("------------------------ Method 1, for Values and Types ------------------------\n");


	PRINT_VALUE_TYPE((long long)10);
	PRINT_VALUE_TYPE((unsigned long long)10);
	PRINT_VALUE_TYPE((long)10);
	PRINT_VALUE_TYPE((unsigned long)10);
	PRINT_VALUE_TYPE((int)10);
	PRINT_VALUE_TYPE((unsigned int)10);
	PRINT_VALUE_TYPE((int)0);
	PRINT_VALUE_TYPE((unsigned int)0);
	// PRINT_VALUE_TYPE(s);			//	wrong
	// PRINT_VALUE_TYPE(us);			//	wrong
	// PRINT_VALUE_TYPE(c);			//	wrong
	// PRINT_VALUE_TYPE(uc);			//	wrong

	// PRINT_TYPE_TYPE(char);			//	wrong
	// PRINT_TYPE_TYPE(unsigned char);			//	wrong
	// PRINT_TYPE_TYPE(short);			//	wrong
	// PRINT_TYPE_TYPE(unsigned short);			//	wrong
	PRINT_TYPE_TYPE(int);
	PRINT_TYPE_TYPE(unsigned int);
	PRINT_TYPE_TYPE(long);
	PRINT_TYPE_TYPE(unsigned long);
	PRINT_TYPE_TYPE(long long);
	PRINT_TYPE_TYPE(unsigned long long);

	printf("\n\n------------------------ Method 2, only for Types ------------------------\n");

	// PRINT_TYPE_TYPE_2(char);			//	wrong
	// PRINT_TYPE_TYPE_2(unsigned char);			//	wrong
	// PRINT_TYPE_TYPE_2(short);			//	wrong
	// PRINT_TYPE_TYPE_2(unsigned short);			//	wrong
	PRINT_TYPE_TYPE_2(int);
	PRINT_TYPE_TYPE_2(unsigned int);
	PRINT_TYPE_TYPE_2(long);
	PRINT_TYPE_TYPE_2(unsigned long);
	PRINT_TYPE_TYPE_2(long long);
	PRINT_TYPE_TYPE_2(unsigned long long);

	printf("\n\n------------------------ Method 3, for Values and Types ------------------------\n");

	PRINT_VALUE_TYPE_3(ll);
	PRINT_VALUE_TYPE_3(ull);
	PRINT_VALUE_TYPE_3(l);
	PRINT_VALUE_TYPE_3(ul);
	PRINT_VALUE_TYPE_3(i);
	PRINT_VALUE_TYPE_3(ui);
	PRINT_VALUE_TYPE_3(i_zero);
	PRINT_VALUE_TYPE_3(ui_zero);
	PRINT_VALUE_TYPE_3(s);
	PRINT_VALUE_TYPE_3(us);
	PRINT_VALUE_TYPE_3(c);
	PRINT_VALUE_TYPE_3(uc);

	PRINT_TYPE_TYPE_3(char);
	PRINT_TYPE_TYPE_3(unsigned char);
	PRINT_TYPE_TYPE_3(short);
	PRINT_TYPE_TYPE_3(unsigned short);
	PRINT_TYPE_TYPE_3(int);
	PRINT_TYPE_TYPE_3(unsigned int);
	PRINT_TYPE_TYPE_3(long);
	PRINT_TYPE_TYPE_3(unsigned long);
	PRINT_TYPE_TYPE_3(long long);
	PRINT_TYPE_TYPE_3(unsigned long long);

	// printf("sizeof(char)=%d, sizeof('a')=%d, sizeof(c)=%d\n", sizeof(char), sizeof('a'), sizeof(c));


    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
