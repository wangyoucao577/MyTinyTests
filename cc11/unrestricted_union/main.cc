
#include "comm_include.h"

union StaticMemberFunctionUnion {
    double d;

    static double GetG(){ return 9.8f; }    //并不占用字节
};

union StaticMemberUnion {
    
    int a;
    double b;

#if defined(_MSC_VER) || defined(__APPLE__)

    //vs2015可以支持静态成员变量, 但GCC编译会失败
    const static int c{1};  //并不占用字节
#endif
};


void TestCase1() {
    ENTER_FUNC;

    StaticMemberFunctionUnion s1{ 0.2f };
    cout << "s1 StaticMemberFunctionUnion.d " << s1.d << endl;
    cout << "s1 StaticMemberFunctionUnion.GetG " << s1.GetG() << endl;
    cout << "s1 StaticMemberFunctionUnion::GetG " << StaticMemberFunctionUnion::GetG() << endl;
    cout << "sizeof(StaticMemberFunctionUnion) " << sizeof(StaticMemberFunctionUnion) << endl;

    cout << "sizeof(StaticMemberUnion) " << sizeof(StaticMemberUnion) << endl;

    //NOTE: 关于Union的初始化
    //从实验结果看, 没有构造函数的union初始化行为是有问题的
    //若{0}初始化，目测效果是类似于memset 0
    //若{非0}初始化, 目测效果是仅设置给第一个成员, 而后续的成员相当于没有初始化
    //比较好的做法还是显式声明构造函数, 也或者把第一个成员定义为占用字节数最多的

    StaticMemberUnion s2{ 0 };
    cout << "s2 StaticMemberUnion.a " << s2.a << endl;
    cout << "s2 StaticMemberUnion.b " << s2.b << endl;
#if defined(_MSC_VER) || defined(__APPLE__)
    cout << "s2 StaticMemberUnion.c " << s2.c << endl;
    cout << "s2 StaticMemberUnion::c " << StaticMemberUnion::c << endl;
#endif

    StaticMemberUnion s3{ 1 };  
    cout << "s3 StaticMemberUnion.a " << s3.a << endl;
    cout << "s3 StaticMemberUnion.b " << s3.b << endl;
#if defined(_MSC_VER) || defined(__APPLE__)
    cout << "s3 StaticMemberUnion.c " << s3.c << endl;
    cout << "s3 StaticMemberUnion::c " << StaticMemberUnion::c << endl;
#endif

#if defined(__APPLE__)
    StaticMemberUnion s4{static_cast<int>(2.2f)};
#else
    StaticMemberUnion s4{ 2.2f };   
#endif
    cout << "s4 StaticMemberUnion.a " << s4.a << endl;
    cout << "s4 StaticMemberUnion.b " << s4.b << endl;
#if defined(_MSC_VER) || defined(__APPLE__)
    cout << "s4 StaticMemberUnion.c " << s4.c << endl;
    cout << "s4 StaticMemberUnion::c " << StaticMemberUnion::c << endl;
#endif

    EXIT_FUNC;
}

union NonPodUnion {
    string s;
    int n;

    NonPodUnion() { new (&s) string(); }    //含有非POD成员时, 需要通过placement new来初始化
    ~NonPodUnion() { s.~string(); }
};

void TestCase2() {

    ENTER_FUNC;

    NonPodUnion t;
    cout << "sizeof(NonPodUnion) " << sizeof(NonPodUnion) << endl;

    EXIT_FUNC;
}

int main() {
    // test codes
    TestCase1();
    TestCase2();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}
