
#include <iostream>
using namespace std;

class MyBase {
public:
    void PrintMyBase() {
        cout << "Call My Base, a_ = " << a_ << endl;
    }

private:
    int a_ { 10 };
};

class InheritOne : MyBase {
public:
    void PrintOne() {
        PrintMyBase();
        cout << "Inherit One from My Base, b_ = " << b_ << endl;
    }

private:
    char b_ {'b'};
};

int main()
{
    InheritOne aOne;
    aOne.PrintOne();
    //aOne.PrintMyBase();   //默认为private继承，故派生类的对象无法直接访问基类的成员和方法, 包括基类的public方法

#if defined(_MSC_VER)
    //wait before return
    cout << "Please press any key to continue..." << endl;
    char a;
    cin >> a;
#endif

}
