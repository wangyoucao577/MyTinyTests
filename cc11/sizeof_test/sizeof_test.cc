#include <iostream>
using namespace std;

struct People {
    int hand;
    static People* all;
};

int main()
{
    People p;
    cout << "sizeof(p.hand): " << sizeof(p.hand) << endl;
    cout << "sizeof(p.all): " << sizeof(p.all) << endl;
    cout << "sizeof(People::all): " << sizeof(People::all) << endl;
    cout << "sizeof(People::hand): " << sizeof(People::hand) << endl; //C++11最新支持
    cout << "sizeof(((People*)0)->hand): " << sizeof(((People*)0)->hand) << endl; //C++11前的技巧

#if defined(_MSC_VER)
    //wait before return
    cout << "Please press any key to continue..." << endl;
    char a;
    cin >> a;
#endif
}