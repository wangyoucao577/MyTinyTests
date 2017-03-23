
#include "comm_include.h"

void TestCase1() {
    ENTER_FUNC;

    cout << R"(hello, \n world)" << endl;
    cout << R"(\u4F60, \n \u597D)" << endl;

    //文件保存为了UTF-8, 以Linux Shell的结果为准
    //字符集这个影响因素真挺多, 有机会好好梳理
    cout << sizeof(u8R"(你好)") << "\t" << u8R"(你好)" << endl;
    cout << sizeof(uR"(你好)") << "\t" << uR"(你好)" << endl;
    cout << sizeof(UR"(你好)") << "\t" << UR"(你好)" << endl;

    EXIT_FUNC;
}

int main() {

    TestCase1();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
    return 0;
}