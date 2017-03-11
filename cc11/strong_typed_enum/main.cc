
#include "comm_include.h"

enum class Type{General, Light, Medium, Heavy};
enum class Cateory{General = 1, Pistol, MachineGun, Cannon};

void TestCase1() {
    ENTER_FUNC;

    Type t = Type::Light;
    if (t > Type::General) {
        cout << "Not General Weapon" << endl;
    }
    if ((int)t > 0) {
        cout << "Not General Weapon" << endl;
    }
    cout << "is_pod<Type>::value " << is_pod<Type>::value << endl;
    cout << "is_pod<Cateory>::value " << is_pod<Cateory>::value << endl;

    EXIT_FUNC;
}

//可以指定存储类型
enum class CCC : char {C1 = 1, C2 = 2};
enum struct DDD : unsigned int {D1 = 1, D2 = 2, DBig = 0xFFFFFFF0U};

void TestCase2() {
    ENTER_FUNC;

    cout << "sizeof(CCC::C1) " << sizeof(CCC::C1) << endl;

    cout << "sizeof(DDD::D1) " << sizeof(DDD::D1) << endl;
    cout << "sizeof(DDD::DBig) " << sizeof(DDD::DBig) << endl;
    cout << "(unsigned int)DDD::DBig " << (unsigned int)DDD::DBig << endl;


    EXIT_FUNC;
}

int main() {

    // test codes
    TestCase1();
    TestCase2();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}