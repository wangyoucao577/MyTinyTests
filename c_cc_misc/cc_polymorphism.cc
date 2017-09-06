
#include <iostream>
using namespace std;

class Fruit
{
public:
    Fruit(){cout << "Fruit Constructor" << endl;}
    
    //基类的析构函数总是应加上virtual
    //这样析构一个指向派生类的基类指针时, 才能正确地调用到派生类的析构函数, 而不仅仅是基类的析构函数
    virtual ~Fruit(){cout << "Fruit Destructor" << endl;}
public:
    virtual void peel() { cout << "peeling Fruit." << endl; }
    
    
};

class Apple : public Fruit
{
public:
    //派生类的构造函数总是会先调用基类的构造函数
    //派生类的析构函数总是会先析构自己, 再调用基类的析构函数
    Apple(){cout << "Apple Constructor" << endl;}
    ~Apple(){cout << "Apple Destructor" << endl;}

public:

    void peel() override { cout << "peeling Apple." << endl; }
};

int main()
{
    Fruit *p = new Apple();

    //若class Fruit中的virtual, 此处会调用class Fruit中的peel，编译居然不报错！
    //加上virtual后, 才正确的调用预期的class Apple的peel
    p->peel();
    delete p;
    
    return 0;
}

