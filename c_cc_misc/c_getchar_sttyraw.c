#include <stdio.h>
#include <sys/ioctl.h>
#include <errno.h>

int kbhit()
{
	int i;
	int ret = ioctl(0, FIONREAD, &i);
	if (0 != ret){
		printf("ioctl FIONREAD on fd %d failed, errno %d\n", 0, errno);
	}
	//printf("kbhit i=%d\n", i);

	return i;	//返回可读取的字符的计数值
}

int main()
{
	int c = ' ';

	printf("press \'q\' to quit\n");

	// terminal设置为单字符模式
	system("stty raw");

	while (c != 'q'){
		if (kbhit() > 0)
		{
			//printf("before getchar\n");
			c = getchar();
			printf("got %c \n", (char)c);
		}
		//usleep(500*1000);
	}

	// terminal恢复为默认的行模式
	system("stty cooked");
    
    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
