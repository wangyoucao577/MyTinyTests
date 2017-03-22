
#include "comm_include.h"


void DoSomething1() { cout << __func__ << endl; }
void DoSomething2() { cout << __func__ << endl; }

// C++11 defined attribute
// [[ attribute-list ]]
[[noreturn]] void ThrowAwayCC11() {
    throw "throwaway";
}

#if defined(__GNUC__)
// GNUC defined attribute
// __attribute__ ((attribute-list))
__attribute__((noreturn)) void ThrowAwayCompilerDefined()
#elif defined(_MSC_VER)
// MSVC defined attribute
// __declspec (extended-decl-modifier)
__declspec(noreturn) void ThrowAwayCompilerDefined()
#else
static_assert(false, "unknown compiler");
#endif
{
    throw "ThrowAwayCompilerDefined";
}

void TestCase1() {
    DoSomething1();
    //两种noreturn都没见编译器有任何优化, 比如warning/error等
    ThrowAwayCompilerDefined();
    ThrowAwayCC11();
    DoSomething2();
}

//TODO: [[carries_dependency]]

int main() {

    TestCase1();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}