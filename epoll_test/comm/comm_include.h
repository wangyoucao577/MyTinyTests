
#ifndef COMM_INCLUDE_H_
#define COMM_INCLUDE_H_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <deque>
#include <map>
#include <type_traits>
#include <utility>
#if defined(_MSC_VER)
#include <conio.h>
#endif
#include <stdint.h>
#include <stdlib.h>

using namespace std;

#define FUNC_ROUTINE_MACRO(pos) (cout << pos << " " << __func__ << endl << endl)
#define ENTER_FUNC FUNC_ROUTINE_MACRO("Enter")
#define EXIT_FUNC FUNC_ROUTINE_MACRO("Exit")

#define VNAME(e) (#e)

#if defined(_MSC_VER)
#define ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS {\
    cout << "Please press any key to continue..." << endl;\
    _getch();\
}
#else
#define ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS (0)
#endif


#endif