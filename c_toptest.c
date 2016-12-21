#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int sleep_us = 1;
	if (argc != 2){
		printf("Usage: \n");
		printf("     toptest sleep_us\n");
		printf("     Example: toptest 1000\n");
		return -1;
	}
	
	sleep_us = atoi(argv[1]);	
    while(1){
    	usleep(sleep_us);	//1ms per sleep
    }

    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
