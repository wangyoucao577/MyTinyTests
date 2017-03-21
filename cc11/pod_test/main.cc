
#include "comm_include.h"
#include "pod_test_types.h"

void TestCase_IsTrivial() {
    ENTER_FUNC;

    cout << is_trivial<Trivial1>::value << endl;
    cout << is_trivial<Trivial2>::value << endl;
    cout << is_trivial<Trivial3>::value << endl;
    cout << is_trivial<Trivial4>::value << endl;
    cout << is_trivial<Trivial5>::value << endl;
    cout << is_trivial<Trivial6>::value << endl;
    cout << is_trivial<NonTrivial1>::value << endl;
    cout << is_trivial<NonTrivial2>::value << endl;
    cout << is_trivial<NonTrivial3>::value << endl;

    EXIT_FUNC;
}

void TestCase_IsStandardLayout_1() {
    ENTER_FUNC;

    cout << is_standard_layout<SL_A1>::value << endl;
    cout << is_standard_layout<SL_A2>::value << endl;
    cout << is_standard_layout<SL_C1>::value << endl;
    cout << is_standard_layout<SL_C2>::value << endl;
    cout << is_standard_layout<SL_C3>::value << endl;
    cout << is_standard_layout<SL_C4>::value << endl;
    cout << is_standard_layout<SL_C5>::value << endl;

    EXIT_FUNC;
}

void TestCase_IsStandardLayout_2() {

    ENTER_FUNC;

    SL_D1 d1;
    SL_D2 d2;

    cout << hex;
    
    cout << reinterpret_cast<long long>(&d1) << endl;
    cout << reinterpret_cast<long long>(&(d1.b)) << endl;
    cout << reinterpret_cast<long long>(&(d1.i)) << endl;
    cout << is_standard_layout<SL_D1>::value << endl;

    cout << reinterpret_cast<long long>(&d2) << endl;
    cout << reinterpret_cast<long long>(&(d2.b)) << endl;
    cout << reinterpret_cast<long long>(&(d2.i)) << endl;
    cout << is_standard_layout<SL_D2>::value << endl;

    EXIT_FUNC;
}

void TestCase_IsStandardLayout_3() {
    ENTER_FUNC;
    cout << is_standard_layout<SLayout1>::value << endl;
    cout << is_standard_layout<SLayout2>::value << endl;
    cout << is_standard_layout<SLayout3>::value << endl;
    cout << is_standard_layout<SLayout4>::value << endl;
    cout << is_standard_layout<SLayout5>::value << endl;
    cout << is_standard_layout<SLayout6>::value << endl;
    cout << is_standard_layout<SLayout7>::value << endl;
    cout << is_standard_layout<NonSLayout1>::value << endl;
    cout << is_standard_layout<NonSLayout2>::value << endl;
    cout << is_standard_layout<NonSLayout3>::value << endl;
    cout << is_standard_layout<NonSLayout4>::value << endl;

    EXIT_FUNC;
}

void TestCase_IsPod_1() {
    ENTER_FUNC;

    cout << is_pod<Trivial1>::value << endl;
    cout << is_pod<Trivial2>::value << endl;
    cout << is_pod<Trivial3>::value << endl;
    cout << is_pod<Trivial4>::value << endl;
    cout << is_pod<Trivial5>::value << endl;
    cout << is_pod<NonTrivial1>::value << endl;
    cout << is_pod<NonTrivial2>::value << endl;
    cout << is_pod<NonTrivial3>::value << endl;

    cout << is_pod<SL_A1>::value << endl;
    cout << is_pod<SL_A2>::value << endl;
    cout << is_pod<SL_C1>::value << endl;
    cout << is_pod<SL_C2>::value << endl;
    cout << is_pod<SL_C3>::value << endl;
    cout << is_pod<SL_C4>::value << endl;
    cout << is_pod<SL_C5>::value << endl;

    cout << is_pod<SL_D1>::value << endl;
    cout << is_pod<SL_D2>::value << endl;

    cout << is_pod<SLayout1>::value << endl;
    cout << is_pod<SLayout2>::value << endl;
    cout << is_pod<SLayout3>::value << endl;
    cout << is_pod<SLayout4>::value << endl;
    cout << is_pod<SLayout5>::value << endl;
    cout << is_pod<SLayout6>::value << endl;
    cout << is_pod<SLayout7>::value << endl;
    cout << is_pod<NonSLayout1>::value << endl;
    cout << is_pod<NonSLayout2>::value << endl;
    cout << is_pod<NonSLayout3>::value << endl;
    cout << is_pod<NonSLayout4>::value << endl;

    EXIT_FUNC;

}

void TestCase_IsPod_2() {
    ENTER_FUNC;

    cout << is_pod<U>::value << endl;
    cout << is_pod<U1>::value << endl;
    cout << is_pod<E>::value << endl;
    cout << is_pod<int>::value << endl;
    cout << is_pod<DA>::value << endl;
    cout << is_pod<PF>::value << endl;


    EXIT_FUNC;

}

int main()
{
    // test codes
    TestCase_IsTrivial();

    TestCase_IsStandardLayout_1();
    TestCase_IsStandardLayout_2();
    TestCase_IsStandardLayout_3();

    TestCase_IsPod_1();
    TestCase_IsPod_2();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}