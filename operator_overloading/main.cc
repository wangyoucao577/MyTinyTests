
#include "SalesData.h"
using namespace std;

int main(){

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

    return 0;
}

