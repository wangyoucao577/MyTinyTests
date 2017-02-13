
#include "comm_include.h"
#include "ILPeople.h"
#include "ILMyData.h"

void TestCase1() {
    int a[] = { 1, 3, 5 };
    int b[] { 2, 4, 6 };

    //通过 initialier_list<T> 实现
    vector<int> c{ 1, 3, 5 };
    map<int, double> d = { {1, 1.0f}, {2, 2.1f}, {3, 3.2f} };

    int *e = new int(1);
    delete e;
    double * f = new double{ 4.3f };
    delete f;
}

void TestCase2() {
    ILPeople p = { {"Garfield", boy}, {"HelloKitty", girl} };
}

void Func(initializer_list<int> iv) {
    for (auto i = iv.begin(); i != iv.end(); ++i)
    {
        cout << __func__ << ": " << *i << endl;
    }
}

void TestCase3() {
    Func({ 1, 3, 5, 7, 9 });
}

void TestCase4() {

    ENTER_FUNC;

    ILMyData d;
    d[{0, 2, 4}] = 1;
    d[{1, 3, 5}] = 2;
    d.Print();

    EXIT_FUNC;
}

int main()
{
    // test codes
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}