
#include "SalesData.h"
#include "StrVec.h"
using namespace std;

void TestCase1(){

    SalesData d(100, 1000);
    cout << d << endl;

    cin >> d;
    cout << d << endl;

    SalesData a(10, 100), b(11, 101);
    d = a + b;
    cout << d << endl;

    d += a;
    cout << d << endl;

    cout << "a == b ? " << (a == b ? "True" : "False") << endl;
    cout << "a != b ? " << (a != b ? "True" : "False") << endl;

}

void TestCase2(){

    StrVec sv;
    cout << "sv = " << sv << endl;
    sv = {"abc", "efg", "testtest"};
    cout << "sv = " << sv << endl;
}

int main(){

    TestCase1();
    TestCase2();

    return 0;
}
