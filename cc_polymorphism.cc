
#include <stdio.h>

class Fruit
{
public:
	virtual void peel() { printf("peeling Fruit.\n"); }
};

class Apple : public Fruit
{
public:
	void peel() { printf("peeling Apple.\n"); }
};

int main()
{
	Fruit *p = new Apple();

	//若class Fruit中的virtual, 此处会调用class Fruit中的peel，编译居然不报错！
	//加上virtual后, 才正确的调用预期的class Apple的peel
	p->peel();
	return 0;
}

