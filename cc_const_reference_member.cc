
#include <iostream>
using namespace std;

class A{
public:
    void Dump(){cout << m_ << endl;}
private:
    int a_ {10};
    int& m_ {a_};
};


class B{
public:
    void Dump(){cout << m_ << endl;}
private:
    const int m_ {11};
};

int main()
{
    A a1;
    A a2(a1);
    a2.Dump();
    A a3 = a1;
    a3.Dump();

    B b1;
    B b2(b1);
    b2.Dump();
    B b3 = b1;
    b3.Dump();

    
    return 0;
}

