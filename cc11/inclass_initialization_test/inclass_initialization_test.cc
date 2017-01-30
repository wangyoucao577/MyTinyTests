
#include <iostream>
#include <string>
using namespace std;

class Mem {
public:
    Mem (int i): m(i) {}

    int Get() { return m; }
private:
    int m;
};

class Group {
public:
    Group() {}
    Group(int a) : data(a) {}
    Group(Mem m) : mem(m) {}
    Group(int a, Mem m, string n): data(a), mem(m), name(n) {}

    void Print() {
        cout << data << " " << mem.Get() << " " << name << endl;
    }
private:
    int data = 1;
    Mem mem{ 0 };
    string name{ "Group" };
};

void TestCase1() {
    Group group1;
    group1.Print();

    Group group2(2);
    group2.Print();

    Group group3(static_cast<Mem>(3));
    group3.Print();

    Group group4(4, 5, "666");
    group4.Print();

}

int main()
{
    TestCase1();

#if defined(_MSC_VER)
    //wait before return
    cout << "Please press any key to continue..." << endl;
    char a;
    cin >> a;
#endif
    return 0;

}