
#include <assert.h>
#include <iostream>
using namespace std;

// 此模板定义不改变class的实际内容, 仅改变其friend属性
template <typename T> class DefenderT {
public:
    friend T;
    void Defence(int x, int y){}
    void Tackle(int x, int y){}

private:
    int pos_x = 15;
    int pos_y = 0;
    int speed = 2;
    int stamina = 12;
};

template <typename T> class AttackerT {
public:
    friend T;
    void Move(int x, int y){}
    void SpeedUp(float ratio){}

private:
    int pos_x = 0;
    int pos_y = -30;
    int speed = 3;
    int stamina = 100;
};

using Defender = DefenderT<int>;
using Attacker = AttackerT<int>;

#ifdef UNIT_TEST
class Validator;
using DefenderTest = DefenderT<Validator>;
using AttackerTest = AttackerT<Validator>;

class Validator {
public:
    void Validate(int x, int y, DefenderTest &d){
        assert(x == d.pos_x && y == d.pos_y);   //friend特性, 可访问其private成员
    }
    void Validate(int x, int y, AttackerTest &a){
        assert(x == a.pos_x && y == a.pos_y);
    }
};

void TestCase()
{
    DefenderTest d;
    AttackerTest a;
    a.Move(15, 30);
    d.Defence(15, 30);
    a.SpeedUp(1.5f);
    d.Defence(15, 30);
    Validator v;
    v.Validate(7, 0, d);
    v.Validate(1, -10, a);
}
#endif

int main()
{
#ifdef UNIT_TEST
    TestCase();
#endif
    

#if defined(_MSC_VER)
    //wait before return
    cout << "Please press any key to continue..." << endl;
    char a;
    cin >> a;
#endif
    return 0;
}
