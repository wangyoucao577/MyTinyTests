#include <sys/ioctl.h>
#include <curses.h>

int kbhit()
{
	int i;
	ioctl(0, FIONREAD, &i);
	return i;	//返回可读取的字符的计数值
}

int main()
{
	int c = ' ';
	int i = 0;

	initscr();
	cbreak();
	noecho();

	mvprintw(0, 0, "Press 'q' to quit\n");
	refresh();
    
    while(c != 'q'){
    	if (kbhit()){
    		c = getchar();
    		mvprintw(1, 0, "got %c\n", c);
    		refresh();
    	}
    }

    nocbreak();
    echo();
    endwin();

    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */
