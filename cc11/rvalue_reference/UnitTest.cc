#include "UnitTest.h"
#include "HasPtrMem.h"
#include "Copyable.h"

#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

#define VNAME(e) (#e)

#define FUNC_ROUTINE_MACRO(pos) (cout << pos << " " << __func__ << endl << endl)
#define ENTER_FUNC FUNC_ROUTINE_MACRO("Enter")
#define EXIT_FUNC FUNC_ROUTINE_MACRO("Exit")


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
    TestCase4();
}

void UnitTest::TestCase1()
{
    ENTER_FUNC;

    HasPtrMem a;
    HasPtrMem b(a);
    cout << *a.d_ << endl;
    cout << *b.d_ << endl;

    EXIT_FUNC;
}

void UnitTest::TestCase2()
{
    ENTER_FUNC;

    HasPtrMem a = HasPtrMem::GetTemp();

    EXIT_FUNC;
}

void UnitTest::TestCase3()
{
    ENTER_FUNC;

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

    EXIT_FUNC;
}

void UnitTest::TestCase4()
{
    ENTER_FUNC;

    cout << "Pass by lvalue " << endl;
    Copyable::AcceptLValue(Copyable::ReturnRValue());

    cout << "Pass by lvalue_reference " << endl;
    Copyable::AcceptLValueReference(Copyable::ReturnRValue());

    cout << "Pass by rvalue_reference " << endl;
    Copyable::AcceptRValueReference(Copyable::ReturnRValue());

    EXIT_FUNC;
}