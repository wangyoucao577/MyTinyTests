
#include "comm_include.h"

void TestCase1() {
    ENTER_FUNC;

    int a = 3, b = 4;
    auto sum1 = [](int x, int y)->int {return x + y; };
    cout << sum1(a, b) << endl;

    auto sum2 = [&] {return a + b; };
    cout << sum2() << endl;

    auto sum3 = [=, &b] {return a + b; };   //按值传递时, 是定义的时候直接传值? 
    a = 5;
    b = 10;
    cout << sum3() << endl;

    auto sum4_plusplus = [=, &b]() mutable {
        a++;
        b++;
        return a + b;
    };
    cout << sum4_plusplus() << endl;

    cout << a << ", " << b << endl;

    EXIT_FUNC;
}

int main() {

    // test codes
    TestCase1();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
    return 0;
}