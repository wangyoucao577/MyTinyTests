#include "UnitTest.h"
#include "HasPtrMem.h"

#include <iostream>
using namespace std;


UnitTest::UnitTest()
{
}


UnitTest::~UnitTest()
{
}

void UnitTest::Run()
{
    TestCase1();
}

void UnitTest::TestCase1()
{
    HasPtrMem a;
    HasPtrMem b(a);
    cout << *a.d_ << endl;
    cout << *b.d_ << endl;
}

