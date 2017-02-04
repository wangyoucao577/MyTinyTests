
#include <iostream>
using namespace std;

int main()
{

#if defined(_MSC_VER)
    //wait before return
    cout << "Please press any key to continue..." << endl;
    char a;
    cin >> a;
#endif
    return 0;
}
