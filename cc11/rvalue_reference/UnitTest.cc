#include "UnitTest.h"
#include "HasPtrMem.h"

#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

#define VNAME(e) (#e)

UnitTest::UnitTest()
{
}


UnitTest::~UnitTest()
{
}

void UnitTest::Run()
{
    //TestCase1();
    TestCase2();
    TestCase3();
}

void UnitTest::TestCase1()
{
    HasPtrMem a;
    HasPtrMem b(a);
    cout << *a.d_ << endl;
    cout << *b.d_ << endl;
}

void UnitTest::TestCase2()
{
    HasPtrMem a = HasPtrMem::GetTemp();
}

void UnitTest::TestCase3()
{
    cout << endl;

    cout << VNAME(is_reference<int>::value) << " " << is_reference<int>::value << endl;
    cout << VNAME(is_reference<int&>::value) << " " << is_reference<int&>::value << endl;
    cout << VNAME(is_reference<const int&>::value) << " " << is_reference<const int&>::value << endl;
    cout << VNAME(is_reference<int&&>::value) << " " << is_reference<int&&>::value << endl;
    cout << VNAME(is_reference<const int&&>::value) << " " << is_reference<const int&&>::value << endl;
    cout << VNAME(is_reference<int*>::value) << " " << is_reference<int*>::value << endl;

    cout << endl;

    cout << VNAME(is_rvalue_reference<int>::value) << " " << is_rvalue_reference<int>::value << endl;
    cout << VNAME(is_rvalue_reference<int&>::value) << " " << is_rvalue_reference<int&>::value << endl;
    cout << VNAME(is_rvalue_reference<const int&>::value) << " " << is_rvalue_reference<const int&>::value << endl;
    cout << VNAME(is_rvalue_reference<int&&>::value) << " " << is_rvalue_reference<int&&>::value << endl;
    cout << VNAME(is_rvalue_reference<const int&&>::value) << " " << is_rvalue_reference<const int&&>::value << endl;
    cout << VNAME(is_rvalue_reference<int*>::value) << " " << is_rvalue_reference<int*>::value << endl;
    
    cout << endl;

    cout << VNAME(is_lvalue_reference<int>::value) << " " << is_lvalue_reference<int>::value << endl;
    cout << VNAME(is_lvalue_reference<int&>::value) << " " << is_lvalue_reference<int&>::value << endl;
    cout << VNAME(is_lvalue_reference<const int&>::value) << " " << is_lvalue_reference<const int&>::value << endl;
    cout << VNAME(is_lvalue_reference<int&&>::value) << " " << is_lvalue_reference<int&&>::value << endl;
    cout << VNAME(is_lvalue_reference<const int&&>::value) << " " << is_lvalue_reference<const int&&>::value << endl;
    cout << VNAME(is_lvalue_reference<int*>::value) << " " << is_lvalue_reference<int*>::value << endl;

}
