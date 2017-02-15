
// SFINEA: Substitution failure is not an error 

#include "comm_include.h"


struct TestA {
    using foo = int;
};

template<typename T>
void f(typename T::foo) { cout << "void f(typename T::foo) " << "called. " << endl; }

template<typename T>
void f(T) { cout << "void f(T) " << "called. " << endl; }

void TestCase1() {
    ENTER_FUNC;

    f<TestA>(10);   //∆•≈‰ void f(typename T::foo)
    f<int>(10); //∆•≈‰ void f(T)

    EXIT_FUNC;
}


int main() {

    // test codes
    TestCase1();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}