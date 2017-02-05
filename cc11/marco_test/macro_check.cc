
#include <iostream>
using namespace std;

#if defined(_MSC_VER)
#if _MSC_VER < 1900
#error "should use at least VS2015"
#endif
#else
#if __cplusplus < 201103L
#error "should use C++11 compiler"
#endif
#endif

//_MSC_VER values on Windows
//MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)
//MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)
//MSVC++ 11.0 _MSC_VER == 1700 (Visual Studio 2012)
//MSVC++ 10.0 _MSC_VER == 1600 (Visual Studio 2010)
//MSVC++ 9.0  _MSC_VER == 1500 (Visual Studio 2008)
//MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)
//MSVC++ 7.1  _MSC_VER == 1310 (Visual Studio 2003)
//MSVC++ 7.0  _MSC_VER == 1300
//MSVC++ 6.0  _MSC_VER == 1200
//MSVC++ 5.0  _MSC_VER == 1100

void stdc_macro_print()
{
    cout << "Standard Clib: " << __STDC_HOSTED__ << endl;
    //cout << "C Standard Version: " << __STDC_VERSION__ << endl;
#if !defined(_MSC_VER)
    // VS2015编译器并未定义这两个宏
    cout << "Standard C: " << __STDC__ << endl;
#if !defined(__APPLE__)
    cout << "ISO/IEC " << __STDC_ISO_10646__ << endl;
#endif
#endif
}

const char* func_marco_test()
{
    cout << "\'__func__\': " << __func__ << endl;
    cout << "\'__FUNCTION__\': " << __FUNCTION__ << endl;

    return __func__;
}

#define MY_PRINTF(format, ...) printf(format, __VA_ARGS__)

int main()
{
	cout << "__cplusplus defined value: " << __cplusplus <<endl;

    stdc_macro_print();
    const char * func_macro_ret = func_marco_test();
    MY_PRINTF("MY_PRINTF %s\n", func_macro_ret);

#if defined(_MSC_VER)
    cout << "MS Ver: " << _MSC_VER << endl << endl;
#endif

#if defined(_MSC_VER)
    //wait before return
    cout << "Please press any key to continue..." << endl;
    char a;
    cin >> a;
#endif
	return 0;
}

