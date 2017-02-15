
#include "comm_include.h"

namespace Jay {
    inline namespace Basic {
        struct Knife { Knife() { cout << "Knife in Basic." << endl; } };
    }

    inline namespace Toolkit {
        template<typename T> class SwissArmyKnife{};
    }

    namespace Other {
        Knife b;    //Knife in Basic
        struct Knife { Knife() { cout << "Knife in Other." << endl; } };
        Knife c;    //Knife in Other
        Basic::Knife k; //Knife in Basic
    }

    namespace NS_ADL {   //test for ADL
        struct A{};
        void ADLFunc(A a) { cout << __func__ << " called." << endl; }
    }
}

namespace Jay {
    //C++11中允许在父命名空间定义/特化子名字空间的模板
    template<> class SwissArmyKnife<Knife>{};
}

using namespace Jay;
int main() {

    // test codes
    
    SwissArmyKnife<Knife> sknife;   //Knife from basic

    //for ADL
    NS_ADL::A a;
    ADLFunc(a); //在已打开的命名空间中找不到, 于是去参数的命名空间中找. 但破坏了封装性.

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}