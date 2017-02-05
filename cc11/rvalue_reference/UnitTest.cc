#include "UnitTest.h"
#include "HasPtrMem.h"

#include <iostream>
using namespace std;

static HasPtrMem GetTemp()
{
    HasPtrMem h;
    return h;
}



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
    HasPtrMem a = GetTemp();
}


