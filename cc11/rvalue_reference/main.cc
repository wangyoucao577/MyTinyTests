
#include <iostream>
using namespace std;

#include "UnitTest.h"

int main()
{
    // test codes
    UnitTest ut;
    ut.Run();

#if defined(_MSC_VER)
    //wait before return
    cout << "Please press any key to continue..." << endl;
    char a;
    cin >> a;
#endif

}