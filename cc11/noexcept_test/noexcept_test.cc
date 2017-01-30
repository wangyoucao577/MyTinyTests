
#include <iostream>
using namespace std;

/////////////// Test Case 1 /////////////////
void Throw() { throw 1; }
void NoBlockThrow() { Throw(); }
void BlockThrow() noexcept { Throw(); }

void TestCase1() {
    try {
        Throw();
    }
    catch (...) {
        cout << "Found Throw." << endl;
    }

    try {
        NoBlockThrow();
    }
    catch (...) {
        cout << "Throw is not blocked." << endl;
    }

    try {
        BlockThrow();
    }
    catch (...) {
        cout << "Block Throw." << endl;
    }
}

/////////////// Test Case 1 /////////////////

/////////////// Test Case 2 /////////////////
struct A {
    ~A() { throw 1; }
};

struct B {
    ~B() noexcept(false) { throw 2; }
};

struct C {
    B b;
};

void funcA() { A a; }
void funcB() { B b; }
void funcC() { C c; }

void TestCase2() {
    try {
        funcB();
    }
    catch (...) {
        cout << "funcB" << endl;
    }

    try {
        funcC();
    }
    catch (...) {
        cout << "funcC" << endl;
    }

    try {
        funcA();
    }
    catch (...) {
        cout << "funcA" << endl;
    }
}
/////////////// Test Case 2 /////////////////

/////////////// noexcept 作为操作符 /////////////////
template <class T>
void funcT() noexcept(noexcept(T())){}
/////////////// noexcept 作为操作符 /////////////////


int main()
{
    TestCase1();
    TestCase2();

#if defined(_MSC_VER)
    //wait before return
    cout << "Please press any key to continue..." << endl;
    char a;
    cin >> a;
#endif

    return 0;
}