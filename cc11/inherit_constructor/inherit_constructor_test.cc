
#include <iostream>
using namespace std;

#define FUNC_ROUTINE_MACRO(pos) (cout << pos << " " << __func__ << endl << endl)
#define ENTER_FUNC FUNC_ROUTINE_MACRO("Enter")
#define EXIT_FUNC FUNC_ROUTINE_MACRO("Exit")

class MyBase {
public:
    MyBase() { cout << "MyBase()" << endl; }
    MyBase(int i) { cout << "MyBase(int)" << endl;}
    MyBase(int i, double d) { cout << "MyBase(int, double)" << endl; }

public:
    void PrintMyBase() {
        cout << "Call My Base, a_ = " << a_ << endl;
    }

private:
    int a_ { 10 };
};

class InheritOne : MyBase {
public:
    InheritOne() : MyBase() { cout << "InheritOne()" << endl; }
    InheritOne(int i) : MyBase(i) { cout << "InheritOne(int)" << endl; }
    InheritOne(int i, double d) : MyBase(i, d) { cout << "InheritOne(int, double)" << endl; }

public:
    void PrintOne() {
        PrintMyBase();
        cout << "Inherit One from My Base, b_ = " << b_ << endl;
    }

private:
    char b_ {'b'};
};

/////////////////////// Test Case /////////////////////////
void TestCase1()
{
    ENTER_FUNC;

    InheritOne aOne;
    aOne.PrintOne();
    //aOne.PrintMyBase();   //默认为private继承，故派生类的对象无法直接访问基类的成员和方法, 包括基类的public方法

    EXIT_FUNC;
}

void TestCase2()
{
    ENTER_FUNC;

    InheritOne aOne = InheritOne();
    InheritOne bOne = InheritOne(10);
    InheritOne cOne = InheritOne(20, 2.2f);

    EXIT_FUNC;
}
/////////////////////// Test Case /////////////////////////

int main()
{
    TestCase1();
    TestCase2();

#if defined(_MSC_VER)
    //wait before return
    cout << "Please press any key to continue..." << endl;
    char a;
    cin >> a;
#endif

}
