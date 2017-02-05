
#include "perfect_forwarding.h"
#include "comm_include.h"


static void RunCode(int && m) {
    cout << "rvalue reference" << endl;
}

static void RunCode(int & m) {
    cout << "lvalue reference" << endl;
}

static void RunCode(const int && m) {
    cout << "const rvalue reference" << endl;
}

static void RunCode(const int & m) {
    cout << "const lvalue reference" << endl;
}

template <typename T>
void PerfectForward(T && t) {
    RunCode(forward<T>(t));
}

void PerfectForwardingTest()
{
    int a = 0;
    const int b = 2;

    PerfectForward(a);
    PerfectForward(move(a));
    PerfectForward(b);
    PerfectForward(move(b));
}