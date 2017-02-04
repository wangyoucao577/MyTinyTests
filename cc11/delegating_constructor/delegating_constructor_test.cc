
#include <iostream>
#include <list>
#include <vector>
#include <deque>
using namespace std;

class Info {
public:
    Info() : Info(1) {}
    Info(int i) : Info(i, 0.1f, 'a') {}
    Info(double d) : Info(1, d, 'a') {}
    Info(char c) : Info(1, 0.1f, c) {}


private:
    Info(int i, double d, char c) : i_(i), d_(d), c_(c) { }

public:
    void Print() { cout << "Values: " << i_ << ", " << d_ << "," << c_ << endl; }

private:
    int i_;
    double d_;
    char c_;
};

class TContructorD {
private:
    template <typename T> TContructorD(T first, T last) {}

public:
    TContructorD(vector<short>& v) : TContructorD(v.begin(), v.end()) {}
    TContructorD(deque<int>& d) : TContructorD(d.begin(), d.end()) {}
};

int main()
{
    Info t = Info();
    t.Print();

#if defined(_MSC_VER)
    //wait before return
    cout << "Please press any key to continue..." << endl;
    char a;
    cin >> a;
#endif

}